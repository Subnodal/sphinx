#include <iostream>

#include "term.h"

using namespace posix;

std::vector<char> StandardTerminal::read(size_t count) {
    std::vector<char> data;

    data.reserve(count);

    char c;

    for (size_t i = 0; i < count; i++) {
        std::cin.get(c);

        data.push_back(c);
    }

    return data;
}

void StandardTerminal::write(const std::vector<char> data) {
    for (char c : data) {
        std::cout << c;
    }
}

bool StandardTerminal::is_available() {
    return std::cin.rdbuf()->in_avail();
}