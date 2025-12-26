#include "sphinx.h"
#include "device.h"

using namespace kernel;

void Sphinx::boot() {
    std::shared_ptr<Device> console = devices.get_boot_console();

    console->println("Hello, world!");
}

void Sphinx::step() {
    schedulers.get(0)->step();
}