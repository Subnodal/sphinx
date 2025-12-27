#include <signal.h>

#include "../../kernel/sphinx.h"
#include "../../kernel/proc.h"
#include "term.h"

using namespace posix;

kernel::Sphinx sphinx;

void interrupt_handler(int signal_code) {
    exit_term_mode();
    exit(0);
}

int main(int argc, char* argv[]) {
    signal(SIGINT, interrupt_handler);
    enter_term_mode();

    std::string std_term_name = sphinx.devices.make_name("tty");
    std::shared_ptr<StandardTerminal> term(new StandardTerminal(std_term_name));

    sphinx.devices.set_boot_console(term);
    sphinx.schedulers.add(std::make_shared<kernel::Scheduler>());

    sphinx.boot();

    while (sphinx.schedulers[0]->step()) {}

    exit_term_mode();
}