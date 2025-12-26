#include "proc.h"

using namespace kernel;

Process::Process(std::string name) {
    _name = name;
}

size_t Process::get_pid() {
    return _pid;
}

void Process::_set_pid(size_t pid) {
    _pid = pid;
}

void Scheduler::add_process(std::shared_ptr<Process> process) {
    process->_set_pid(_next_pid++);

    _processes.push_back(process);
}

void Scheduler::step() {
    for (std::shared_ptr<Process> process : _processes) {
        process->_step();
    }
}