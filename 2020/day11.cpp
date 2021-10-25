#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

uint64_t square(const uint64_t num) {
    return num * num;
}

int main(void) {
    uint64_t num;

    std::cout << "Enter a number" << std::endl;
    std::cin >> num;

    for (uint64_t i = 1; i <= num; i++) { std::cout << square(i) << std::endl; }

    return 0;
}