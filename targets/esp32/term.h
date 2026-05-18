#ifndef ESP32_TERM_H_
#define ESP32_TERM_H_

#include "kernel/device.h"

namespace esp32 {
    class UartTerminal : public kernel::Device {
        public:
            using Device::Device;

            std::vector<char> read(size_t count) override;
            void write(const std::vector<char> data) override;
            bool is_available() override;
    };
}

#endif