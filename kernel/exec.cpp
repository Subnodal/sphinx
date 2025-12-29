#include "exec.h"

using namespace kernel;

void Interpreters::add(std::shared_ptr<Interpreter> interpreter) {
    _entries.push_back(interpreter);
}

std::shared_ptr<Process> Interpreters::create_process(SeekableFile* file) {
    for (std::shared_ptr<Interpreter> interpreter : _entries) {
        std::shared_ptr<Process> process = interpreter->create_process(file);

        if (process) {
            return process;
        }
    }

    return nullptr;
}