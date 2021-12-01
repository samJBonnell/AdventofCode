#include <iostream>
#include <iterator>
#include <vector>

int main(void) {
    std::istream_iterator<int> in(std::cin), eof;
    std::vector<int> depths(in, eof);

    uint64_t increases = 0;

    for (auto it = depths.begin(), offset = depths.begin() + 1, end = depths.end(); offset != end; it++, offset++) {
        increases += (offset > it) ? 1 : 0;
    }

    std::cout << std::endl << increases << std::endl;

    return 0;
}