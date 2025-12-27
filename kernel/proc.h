#ifndef KERNEL_PROC_H_
#define KERNEL_PROC_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

namespace kernel {
    typedef size_t pid_t;
    typedef std::vector<std::string> argv_t;
    typedef std::map<std::string, std::string> env_t;

    enum class ProcessState {
        CONFIGURING,
        RUNNING,
        ZOMBIE
    };

    class ProcessError : public std::runtime_error {
        public:
            ProcessError(const std::string& what);
    };

    class Process {
        public:
            Process(std::string name);

            ProcessState get_state();
            size_t get_pid();
            std::string get_name();
            std::shared_ptr<const argv_t> get_argv();
            void set_argv(std::shared_ptr<argv_t> argv);
            std::shared_ptr<const env_t> get_env();
            void set_env(std::shared_ptr<env_t> env);

        private:
            friend class Scheduler;

            ProcessState _state = ProcessState::CONFIGURING;
            size_t _pid = -1;
            std::string _name;
            std::shared_ptr<argv_t> _argv;
            std::shared_ptr<env_t> _env;

            virtual bool _step() = 0;
    };

    class Scheduler {
        public:
            void add_process(std::shared_ptr<Process> process);

            bool step();

        private:
            std::vector<std::shared_ptr<Process>> _processes;
            size_t _next_pid = 0;
    };

    class Schedulers {
        public:
            void add(std::shared_ptr<Scheduler> scheduler);

            std::shared_ptr<Scheduler> operator[](size_t index);

        private:
            std::vector<std::shared_ptr<Scheduler>> _schedulers;
    };
}

#endif