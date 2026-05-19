#include "../../kernel/sphinx.h"
#include "../../kernel/proc.h"
#include "term.h"

using namespace esp32;

kernel::Sphinx sphinx;

extern "C" void app_main() {
    std::string std_term_name = sphinx.devices.make_name("tty");
    std::shared_ptr<UartTerminal> term(new UartTerminal(std_term_name, UART_NUM_0));

    sphinx.devices.set_boot_console(term);
    sphinx.schedulers.add(std::make_shared<kernel::Scheduler>());

    sphinx.boot();

    while (sphinx.schedulers[0]->step()) {}

    while (true) {
        term->write(term->read(1));
    }
}