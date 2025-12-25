#include "stream.h"

using namespace kernel;

void Stream::print(const char c) {
    std::vector<char> data_vector {c};

    write(data_vector);
}

void Stream::print(const std::string data) {
    std::vector<char> data_vector(data.begin(), data.end());

    write(data_vector);
}

void Stream::println(const char c) {
    print(c);
    print('\n');
}

void Stream::println(const std::string data) {
    print(data);
    print('\n');
}