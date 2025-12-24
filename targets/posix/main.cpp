#include "../../kernel/sphinx.h"
#include "term.h"

using namespace posix;

kernel::Sphinx sphinx;

int main(int argc, char* argv[]) {
    std::string std_term_name = sphinx.devices.make_name("Terminal");
    std::shared_ptr<StandardTerminal> term(new StandardTerminal(std_term_name));

    sphinx.devices.set_boot_console(term);

    sphinx.boot();
}