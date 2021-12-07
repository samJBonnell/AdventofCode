#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <functional>

// Function Prototypes

uint16_t getBits(const std::vector<uint16_t>& binary, const uint16_t& inputLength, std::function<bool(const uint16_t&, const uint16_t&)> comp);
bool nthBit(uint16_t& number, uint16_t index);
void finalEntry(std::vector<uint16_t>& vec, uint16_t index, std::function<bool(const uint16_t&, const uint16_t&)> comp);

int main(void) {
    std::istream_iterator<std::string> in(std::cin),  eof;
    std::vector<std::string> input(in, eof);
    std::vector<uint16_t> binary;

    uint16_t inputLength = input[0].length() - 1;
    uint16_t gamma = 0, epsilon = 0;

    for (const auto& string : input) { binary.push_back(std::stoi(string, 0, 2)); }
    std::vector<uint16_t> binaryCopy(binary);

    // Part One

    gamma = getBits(binary, inputLength, [](uint16_t lhs, uint16_t rhs) -> bool { return (lhs >= rhs); });
    for (std::string::size_type i = 0; i <= inputLength; i++) { epsilon |= (~(gamma >> i) & 1) << (i); }

    // Part Two

    finalEntry(binary,      inputLength, [](uint16_t lhs, uint16_t rhs) -> bool { return (lhs >= rhs); });
    finalEntry(binaryCopy,  inputLength, [](uint16_t lhs, uint16_t rhs) -> bool { return (lhs < rhs); });

    // Output

    std::cout << std::endl << "Part One:" << std::endl << gamma * epsilon << std::endl << gamma << " " << epsilon << std::endl << std::endl;
    std::cout << "Part Two" << std::endl << binary[0] * binaryCopy[0] << std::endl << binary[0] << " " << binaryCopy[0] << std::endl;

    return 0;
}

/*

Determine the most common bit at each index from a list of uint16_t's. 
Using lambda comp(), determine if a 1 or 0 should be set in an output number based on commanality.

*/

uint16_t getBits(const std::vector<uint16_t>& binary, const uint16_t& inputLength, std::function<bool(const uint16_t&, const uint16_t&)> comp) {
    uint16_t oneBit = 0, zeroBit = 0;
    uint16_t gamma = 0;

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

bool nthBit(uint16_t& number, uint16_t index) { // Return the value of the nth bit in a number
    return ((number >> index) & 1);
}

void finalEntry(std::vector<uint16_t>& vec, uint16_t index, std::function<bool(const uint16_t&, const uint16_t&)> comp) {
    uint16_t bitMask = 0;

    while (vec.size() != 1) {
            bitMask = getBits(vec, index, comp);
            for (auto it = vec.begin(); it != vec.end();) {
                if (nthBit(bitMask, index) != nthBit(*it, index)) it = vec.erase(it);
                else {
                    it++;
                }
            }

            index--;
    }

    return;
}