#ifndef ESP32_TERM_H_
#define ESP32_TERM_H_

#include "driver/uart.h"

#include "kernel/device.h"

namespace esp32 {
    typedef uart_port_t uart_port_t;

    class UartTerminal : public kernel::Device {
        public:
            UartTerminal(const std::string name, uart_port_t port);

            std::vector<char> read(size_t count) override;
            void write(const std::vector<char> data) override;
            bool is_available() override;

        private:
            uart_port_t _port;
    };
}

#endif