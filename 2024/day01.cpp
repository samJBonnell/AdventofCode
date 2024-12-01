#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <set>
#include <cmath>
#include <algorithm>

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> input(in, eof);

    std::multiset<int> leftList, rightList;
    uint32_t index = 0;
    uint32_t distance = 0;
    uint32_t similarityScore = 0;

    std::cout << std::endl << "Start of Output" << std::endl;
    for (const auto& ptr : input) {
        if (index++ % 2 == 0) leftList.insert(std::stoi(ptr));
        else rightList.insert(std::stoi(ptr));
    }

    std::multiset<int>::iterator ptrLeft = leftList.begin(), endLeft = leftList.end();
    std::multiset<int>::iterator ptrRight = rightList.begin(), endRight = rightList.end();

    while (ptrLeft != endLeft) distance += std::abs(*(ptrLeft++) - *(ptrRight++));

    uint32_t tempSimilarity = 0;
    ptrRight = rightList.begin(), endRight = rightList.end();
    for (const auto& ptrLeft : leftList) {
        similarityScore += (ptrLeft * std::count(ptrRight, endRight, ptrLeft));
    }

    std::cout << "Part One: " << std::endl;
    std::cout << distance << std::endl;

    std::cout << std::endl;
    std::cout << "Part Two: " << std::endl;
    std::cout << similarityScore << std::endl;

    return 0;
}