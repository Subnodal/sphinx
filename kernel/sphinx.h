#ifndef KERNEL_SPHINX_H_
#define KERNEL_SPHINX_H_

#include "device.h"

namespace kernel {
    class Sphinx {
        public:
            Devices devices;

            void boot();
    };
}

#endif