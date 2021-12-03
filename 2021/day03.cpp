#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <functional>

uint16_t mostcommonBits(const std::vector<uint16_t>& binary, const uint16_t& inputLength, std::function<bool(const uint16_t&, const uint16_t&)> comp);

int main(void) {
    std::istream_iterator<std::string> in(std::cin),  eof;
    std::vector<std::string> input(in, eof);
    std::vector<uint16_t> binary;

    for (const auto& string : input) {
        binary.push_back(std::stoi(string, 0, 2));
    }

    uint16_t inputLength = input[0].length() - 1;

    // Part One

    uint16_t gamma = 0, epsilon = 0;

    gamma = mostcommonBits(binary, inputLength, [](uint16_t first, uint16_t second) -> bool { return (first >= second); });

    for (std::string::size_type i = 0; i <= inputLength; i++) {
        epsilon |= (~(gamma >> i) & 1) << (i);
    }

    std::cout << gamma * epsilon << std::endl;
    std::cout << gamma << " " << epsilon << std::endl;

    // Part Two



    return 0;
}

uint16_t mostcommonBits(const std::vector<uint16_t>& binary, const uint16_t& inputLength, std::function<bool(const uint16_t&, const uint16_t&)> comp) {
    uint16_t oneBit = 0, zeroBit = 0;
    uint16_t gamma = 0, epsilon = 0;

    for (std::string::size_type i = 0; i <= inputLength; i++) {
        for (const auto& number : binary) {
            if(((number >> inputLength - i) & 1) == 1) oneBit++;
            else {
                zeroBit++;
            }
        }

        if (comp(oneBit, zeroBit)) gamma |= 1 << (inputLength - i);

        oneBit = 0;
        zeroBit = 0;
    }

    return gamma;
}