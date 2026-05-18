#include <iostream>

#include "term.h"

using namespace esp32;

std::vector<char> UartTerminal::read(size_t count) {
    std::vector<char> data;

    data.reserve(count);

    char c;

    for (size_t i = 0; i < count; i++) {
        std::cin.get(c);

        data.push_back(c);
    }

    return data;
}

void UartTerminal::write(const std::vector<char> data) {
    for (char c : data) {
        std::cout << c;
    }
}

bool UartTerminal::is_available() {
    return std::cin.rdbuf()->in_avail();
}