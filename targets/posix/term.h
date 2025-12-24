#ifndef POSIX_TERM_H_
#define POSIX_TERM_H_

#include "../../kernel/device.h"

namespace posix {
    class StandardTerminal : public kernel::Device {
        public:
            using Device::Device;

            std::vector<char> read(size_t count) override;
            void write(const std::vector<char> data) override;
            bool is_available() override;
    };
}

#endif