#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <array>

uint64_t joltageDifference(std::vector<uint64_t>::iterator& first, std::vector<uint64_t>::iterator& second);
uint64_t pathways(std::vector<uint64_t>& joltageAdaptors);

int main(void) {
    std::istream_iterator<uint64_t> in(std::cin), eof;
    std::vector<uint64_t> joltageAdaptors(in, eof);
    std::map<uint64_t, uint64_t> deltaJolt;

    std::sort(joltageAdaptors.begin(), joltageAdaptors.end());

    joltageAdaptors.insert(joltageAdaptors.begin(), 0); // Insert the starting terminal with a joltage of 0;
    joltageAdaptors.push_back(*std::max_element(joltageAdaptors.begin(), joltageAdaptors.end()) + 3);

    for (auto it = joltageAdaptors.begin(), it2 = joltageAdaptors.begin() + 1, end = joltageAdaptors.end(); it2 != end; it++, it2++) {
        deltaJolt[joltageDifference(it, it2)]++;
    }
    
    std::cout << deltaJolt[1] * deltaJolt[3] << std::endl;
    std::cout << pathways(joltageAdaptors) << std::endl;

    return 0;
}

uint64_t joltageDifference(std::vector<uint64_t>::iterator& first, std::vector<uint64_t>::iterator& second) {
    return *second - *first;
}

uint64_t pathways(std::vector<uint64_t>& joltageAdaptors) { // Code structure taken from Joel Grus' implementation in Python and ported to C++. I was unable to figure out an efficient algorithm and worked with lots of permutations for a rather long time.
    std::vector<uint64_t> numPaths(*std::max_element(joltageAdaptors.begin(), joltageAdaptors.end()) + 1, 0);

    numPaths[0] = 1;

    if (std::find(joltageAdaptors.begin(), joltageAdaptors.end(), 1) != joltageAdaptors.end()) numPaths[1] = 1;
    if (std::find(joltageAdaptors.begin(), joltageAdaptors.end(), 1) != joltageAdaptors.end() && std::find(joltageAdaptors.begin(), joltageAdaptors.end(), 2) != joltageAdaptors.end()) numPaths[2] = 2;
    else if (std::find(joltageAdaptors.begin(), joltageAdaptors.end(), 2) != joltageAdaptors.end()) { numPaths[2] = 1; }

    for (const auto& adaptor : joltageAdaptors) {
        if (adaptor == 0 || adaptor == 1 || adaptor == 2) continue;

        numPaths[adaptor] = numPaths[adaptor-3] + numPaths[adaptor-2] + numPaths[adaptor-1];
    }

    return numPaths[*std::max_element(joltageAdaptors.begin(), joltageAdaptors.end())];
}