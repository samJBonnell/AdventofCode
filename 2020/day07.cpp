#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

int main(void) {
    std::vector<std::string> input;
    std::string inString;

    while (std::getline(std::cin, inString)) { input.push_back(inString); } // Fill the input vector with the lines from the console input

    for (const auto& ptr : input) std::cout << ptr << std::endl;

    return 0;
}