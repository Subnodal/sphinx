#ifndef KERNEL_SPHINX_H_
#define KERNEL_SPHINX_H_

#include "device.h"
#include "proc.h"
#include "fs.h"
#include "exec.h"

namespace kernel {
    class Sphinx {
        public:
            Devices devices;
            Schedulers schedulers;
            FilesystemTable filesystem_table;
            Interpreters interpreters;

            void boot();
    };
}

#endif