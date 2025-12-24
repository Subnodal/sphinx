#include "sphinx.h"
#include "device.h"

using namespace kernel;

void Sphinx::boot() {
    std::shared_ptr<Device> console = devices.get_boot_console();
    std::string hello = "Hello, world!\n";
    std::vector<char> hello_vector(hello.begin(), hello.end());

    console->write(hello_vector);
}