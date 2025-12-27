#include <algorithm>

#include "device.h"

using namespace kernel;

DeviceError::DeviceError(const std::string& what = "")
: std::runtime_error(what) {}

Device::Device(const std::string name)
: _name(name) {}

const std::string Device::get_name() {
    return _name;
}

std::shared_ptr<Device> Devices::get_by_name(std::string name) {
    for (auto device : _entries) {
        if (device->get_name() == name) {
            return device;
        }
    }
    
    return nullptr;
}

std::string Devices::make_name(std::string base_name) {
    size_t index = 1;
    std::string name = base_name + "0";

    while (get_by_name(name)) {
        name = base_name + std::to_string(index++);
    }

    return name;
}

void Devices::add(std::shared_ptr<Device> device) {
    if (get_by_name(device->get_name())) {
        throw DeviceError("device with same name already exists");
    }

    _entries.push_back(device);
}

bool Devices::has(std::shared_ptr<Device> device) {
    return std::find(_entries.begin(), _entries.end(), device) != _entries.end();
}

std::shared_ptr<Device> Devices::get_boot_console() {
    return _boot_console;
}

void Devices::set_boot_console(std::shared_ptr<Device> device) {
    if (!has(device)) {
        add(device);
    }

    _boot_console = device;
}