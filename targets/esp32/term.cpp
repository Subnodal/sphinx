#include "term.h"

#define UART_BUFFER_SIZE 1024

using namespace esp32;

// TODO: Make UART a standard kernel interface, with lots of config options
UartTerminal::UartTerminal(const std::string name, uart_port_t port)
: Device::Device(name)
, _port(port) {
    uart_config_t config {};

    config.baud_rate = 115200;
    config.data_bits = UART_DATA_8_BITS;
    config.parity = UART_PARITY_DISABLE;
    config.stop_bits = UART_STOP_BITS_1;
    config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    config.source_clk = UART_SCLK_DEFAULT;

    uart_driver_install(port, UART_BUFFER_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(port, &config);
}

std::vector<char> UartTerminal::read(size_t count) {
    std::vector<char> data;

    data.reserve(count);

    char c;

    for (size_t i = 0; i < count; i++) {
        bool read = uart_read_bytes(_port, &c, 1, pdMS_TO_TICKS(100));

        if (read) {
            data.push_back(c);
        }
    }

    return data;
}

void UartTerminal::write(const std::vector<char> data) {
    uart_write_bytes(_port, data.data(), data.size());
}

bool UartTerminal::is_available() {
    size_t available;

    ESP_ERROR_CHECK_WITHOUT_ABORT(uart_get_buffered_data_len(_port, &available));

    return available;
}