#include "sphinx.h"
#include "device.h"
#include "fs/bifs/bifs.h"

using namespace kernel;

void Sphinx::boot() {
    std::shared_ptr<Device> console = devices.get_boot_console();
    auto bifs = std::make_shared<bifs::BuiltInFilesystem>("/bin");

    filesystem_table.add(bifs);

    std::string test_text = "This is a test file!\n";
    auto test_data = std::make_shared<std::vector<char>>(test_text.begin(), test_text.end());

    bifs->add_file("/test.txt", test_data);

    console->println("Hello, world!");

    std::shared_ptr<File> test_file = filesystem_table.open("/bin/test.txt", FileMode::READ);

    if (!test_file) {
        console->println("File not found");
        return;
    }

    console->write(test_file->read(-1));
}