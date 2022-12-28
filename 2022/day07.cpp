#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "day07.hpp"

int main(void) {
    std::istream_iterator<std::string> in(std::cin), end;
    std::vector<std::string> terminalOutput(in, end);

    for (const auto& line : terminalOutput) {
        
    }

    return 0;
}