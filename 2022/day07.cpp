#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "day07.hpp"

int main(void) {
    std::istream_iterator<std::string> in(std::cin), end;
    std::vector<std::string> terminalOutput(in, end);

    for (const auto& line : terminalOutput) { // For each of the rows of the terminal, 
        if (line.front() == '$') { // Current line is a command
            return;
        }
    }

    return 0;
}