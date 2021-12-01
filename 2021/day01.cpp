#include <iostream>
#include <iterator>
#include <vector>

void partOne(std::vector<int>::iterator it, std::vector<int>::iterator end, uint64_t& increases);
void partTwo(std::vector<int>::iterator it, std::vector<int>::iterator end, uint64_t& increases);

int main(void) {
    std::istream_iterator<int> in(std::cin), eof;
    std::vector<int> depths(in, eof);

    uint64_t increasePartOne = 0;
    uint64_t increasePartTwo = 0;

    partOne(depths.begin(), depths.end(), increasePartOne);
    partTwo(depths.begin(), depths.end(), increasePartTwo);

    std::cout << std::endl <<  "Part One: " << increasePartOne << std::endl;
    std::cout <<               "Part Two: " << increasePartTwo << std::endl;

    return 0;
}

void partOne(std::vector<int>::iterator it, std::vector<int>::iterator end, uint64_t& increases) { // Part One
    for (auto offset = it + 1; offset != end; it++, offset++) {
        increases += (*offset > *it) ? 1 : 0;
    }

    return;
}

void partTwo(std::vector<int>::iterator it, std::vector<int>::iterator end, uint64_t& increases) { // Part Two
    std::vector<int>::iterator offsetOne = it + 1, offsetTwo = it + 2;
    uint64_t currentSum, previousSum = 0;

    for(;offsetTwo != end; it++, offsetOne++, offsetTwo++) {
        currentSum = *it + *offsetOne + *offsetTwo;
        if (previousSum) increases += (currentSum > previousSum) ? 1 : 0;
        previousSum = currentSum;
    }

    return;
}