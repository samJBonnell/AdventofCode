#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iterator>
#include <sstream>
#include <map>

// Move through the string and replace all string numbers with real numbers.
// Move through string and find first and last digit
// Continue as before

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> input(in, eof);
    std::string::iterator start;
    std::string::reverse_iterator end;

    std::vector<std::string> key = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    uint32_t calibrationSum = 0;

    for (auto string : input) {
        start = string.begin();
        end = string.rbegin();
        for (int i = 0; i < 9; i++) {
            auto index = string.find(key[i]);
            if (index != std::string::npos) {
                string.replace(index, key[i].length(), std::to_string(i+1));
            }
        }

        while (!std::isdigit(*start) && start != string.end()) start++;
        while (!std::isdigit(*end) && end != string.rend()) end++;
        calibrationSum += 10*(*(start)-(int)48) + (*end - (int)48);

        std::cout << (*(start)-(int)48) << (*end - (int)48) << std::endl << std::endl;
    }

    std::cout << "Part One: " << calibrationSum << std::endl;
    return 0;
}