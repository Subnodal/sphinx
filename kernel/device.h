#ifndef KERNEL_DEVICE_H_
#define KERNEL_DEVICE_H_

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "stream.h"

namespace kernel {
    class DeviceError : public std::runtime_error {
        public:
            DeviceError(const std::string& what);
    };

    class Device : public Stream {
        public:
            Device(const std::string name);

            const std::string get_name();

            virtual bool is_available() = 0;

        private:
            const std::string _name;
    };

    class Devices {
        public:
            std::shared_ptr<Device> get_by_name(std::string name);
            std::string make_name(std::string base_name);

            void add(std::shared_ptr<Device> device);
            bool has(std::shared_ptr<Device> device);

            std::shared_ptr<Device> get_boot_console();
            void set_boot_console(std::shared_ptr<Device> device);

        private:
            std::vector<std::shared_ptr<Device>> _entries;
            std::shared_ptr<Device> _boot_console;
    };
}

#endif