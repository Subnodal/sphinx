#ifndef KERNEL_PROC_H_
#define KERNEL_PROC_H_

#include <string>
#include <vector>
#include <memory>

namespace kernel {
    class Process {
        public:
            Process(std::string name);

            size_t get_pid();

        private:
            friend class Scheduler;

            size_t _pid;
            std::string _name;

            void _set_pid(size_t pid);
            virtual void _step() = 0;
    };

    class Scheduler {
        public:
            void add_process(std::shared_ptr<Process> process);

            void step();

        private:
            std::vector<std::shared_ptr<Process>> _processes;
            size_t _next_pid = 0;
    };

    class Schedulers {
        public:
            void add(std::shared_ptr<Scheduler> scheduler);

            std::shared_ptr<Scheduler> get(size_t index);

        private:
            std::vector<std::shared_ptr<Scheduler>> _schedulers;
    };
}

#endif