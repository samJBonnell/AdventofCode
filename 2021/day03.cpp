#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <map>

int main(void) {
    std::istream_iterator<std::string> in(std::cin),  eof;
    std::vector<std::string> input(in, eof);
    std::vector<uint16_t> binary;

    for (const auto& string : input) {
        binary.push_back(std::stoi(string, 0, 2));
    }

    // Part One

    uint16_t oneBit = 0, zeroBit = 0;
    uint16_t gamma = 0, epsilon = 0;

    for (std::string::size_type i = 0; i < input[0].length(); i++) {
        for (const auto& number : binary) {
            if(((number >> input[0].length() - i - 1) & 1) == 1) oneBit++;
            else {
                zeroBit++;
            }
        }

        if (oneBit >= zeroBit) gamma |= 1 << (input[0].length() - i - 1);

        oneBit = 0;
        zeroBit = 0;
    }

    for (std::string::size_type i = 0; i < input[0].length(); i++) {
        epsilon |= (~(gamma >> i) & 1) << (i);
    }

    std::cout << gamma * epsilon << std::endl;
    std::cout << gamma << " " << epsilon << std::endl;

    // Part Two

    std::vector<uint16_t> binaryCopy;

    for (const auto& element : binary) {
        binaryCopy.push_back(element);
    }

    uint16_t index = input[0].length() - 1;

    oneBit = 0;
    zeroBit = 0;
    gamma = 0;
    epsilon = 0;

    while (binary.size() != 1) {
        for (std::string::size_type i = 0; i < input[0].length(); i++) {
            for (const auto& number : binary) {
                if(((number >> input[0].length() - i - 1) & 1) == 1) oneBit++;
                else {
                    zeroBit++;
                }
            }

            if (static_cast<float>(oneBit)/binary.size() >= static_cast<float>(zeroBit)/binary.size()) gamma |= 1 << (input[0].length() - i - 1);

            oneBit = 0;
            zeroBit = 0;
        }

        // Find oxygen number

        for (auto it = binary.begin(); it != binary.end() && binary.size() != 1;) {
            if (((gamma >> index) & 1) != ((*it >> index) & 1)) {
                it = binary.erase(it);
            }
            else {
                it++;
            }
        }

        index--;
        
    }

    index = input[0].length() - 1;

    oneBit = 0;
    zeroBit = 0;
    gamma = 0;
    epsilon = 0;

    while (binaryCopy.size() != 1) {
        for (std::string::size_type i = 0; i < input[0].length(); i++) {
            for (const auto& number : binaryCopy) {
                if(((number >> input[0].length() - i - 1) & 1) == 1) oneBit++;
                else {
                    zeroBit++;
                }
            }

            if (static_cast<float>(oneBit)/binaryCopy.size() < static_cast<float>(zeroBit)/binaryCopy.size()) gamma |= 1 << (input[0].length() - i - 1);

            oneBit = 0;
            zeroBit = 0;
        }

        for (std::string::size_type i = 0; i < input[0].length(); i++) {
            epsilon |= (~(gamma >> i) & 1) << (i);
        }

        // Find CO2 number

        for (auto it = binaryCopy.begin(); it != binaryCopy.end() && binaryCopy.size() != 1;) {
            if (((gamma >> index) & 1) != ((*it >> index) & 1)) {
                it = binaryCopy.erase(it);
            }
            else {
                it++;
            }
        }

        index--;
    }

    std::cout << std::endl<< binary[0] * binaryCopy[0] << std::endl;
    std::cout << binary[0] << " " << binaryCopy[0] << std::endl;

    return 0;
}