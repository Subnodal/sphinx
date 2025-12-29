#ifndef KERNEL_EXEC_H_
#define KERNEL_EXEC_H_

#include <memory>

#include "proc.h"
#include "fs.h"

namespace kernel {
    class Interpreter {
        public:
            virtual std::shared_ptr<Process> create_process(SeekableFile* file) = 0;
    };

    class Interpreters {
        public:
            void add(std::shared_ptr<Interpreter> interpreter);

            std::shared_ptr<Process> create_process(SeekableFile* file);

        private:
            std::vector<std::shared_ptr<Interpreter>> _entries;
    };
}

#endif