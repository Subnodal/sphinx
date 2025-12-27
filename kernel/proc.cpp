#include "proc.h"

using namespace kernel;

ProcessError::ProcessError(const std::string& what = "")
: std::runtime_error(what) {}

Process::Process(std::string name) {
    _name = name;
    _argv = std::make_shared<argv_t>();
    _env = std::make_shared<env_t>();
}

ProcessState Process::get_state() {
    return _state;
}

size_t Process::get_pid() {
    return _pid;
}

std::string Process::get_name() {
    return _name;
}

std::shared_ptr<const argv_t> Process::get_argv() {
    return _argv;
}

void Process::set_argv(std::shared_ptr<argv_t> argv) {
    if (_state != ProcessState::CONFIGURING) {
        throw ProcessError("process already configured");
    }

    _argv = argv;
}

std::shared_ptr<const env_t> Process::get_env() {
    return _env;
}

void Process::set_env(std::shared_ptr<env_t> env) {
    if (_state != ProcessState::CONFIGURING) {
        throw ProcessError("process already configured");
    }

    _env = env;
}

void Scheduler::add_process(std::shared_ptr<Process> process) {
    process->_state = ProcessState::RUNNING;
    process->_pid = _next_pid++;

    _processes.push_back(process);
}

bool Scheduler::step() {
    bool any_process_run = false;

    for (std::shared_ptr<Process> process : _processes) {
        if (process->_state == ProcessState::RUNNING) {
            any_process_run = true;

            if (!process->_step()) {
                process->_state = ProcessState::ZOMBIE;
            }
        }
    }

    return any_process_run;
}

void Schedulers::add(std::shared_ptr<Scheduler> scheduler) {
    _schedulers.push_back(scheduler);
}

std::shared_ptr<Scheduler> Schedulers::operator[](size_t index) {
    return _schedulers[index];
}