#include <iostream>
#include <termios.h>

#include "term.h"

using namespace posix;

struct termios original_term = {0};

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

void posix::enter_term_mode() {
    struct termios term;

    tcgetattr(fileno(stdin), &term);
    
    original_term = term;

    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;

    tcsetattr(fileno(stdin), TCSANOW, &term);
}

void posix::exit_term_mode() {
    tcsetattr(fileno(stdin), TCSANOW, &original_term);
}