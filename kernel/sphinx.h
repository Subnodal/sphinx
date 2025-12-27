#ifndef KERNEL_SPHINX_H_
#define KERNEL_SPHINX_H_

#include "device.h"
#include "proc.h"

namespace kernel {
    class Sphinx {
        public:
            Devices devices;
            Schedulers schedulers;

            void boot();
    };
}

#endif