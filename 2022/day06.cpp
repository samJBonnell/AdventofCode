#include <iostream>
#include <iterator>
#include <set>

const uint32_t SIGNAL_LENGTH = 3;
const uint32_t MESSAGE_LENGTH = 13;

std::string::iterator& checkSignal(std::string::iterator& first, std::string::iterator& second, std::string::iterator& end);

int main(void) {
    std::istream_iterator<char> in(std::cin), eof;
    std::string signal(in, eof);

    std::string::iterator begin = signal.begin();
    std::string::iterator first = signal.begin();
    std::string::iterator second = signal.begin() + SIGNAL_LENGTH;
    std::string::iterator end = signal.end();

    std::cout << "Part One" << std::endl << std::distance(begin, checkSignal(first, second, end)) << std::endl;

    first = signal.begin();
    second = signal.begin() + MESSAGE_LENGTH;

    std::cout << "Part Two" << std::endl << std::distance(begin, checkSignal(first, second, end)) << std::endl;

    return 0;
}

std::string::iterator& checkSignal(std::string::iterator& first, std::string::iterator& second, std::string::iterator& end) {
    uint32_t difference = second - first;
    std::set<char> tempSet;

    while (second != end) {
        std::string::iterator tempFirst = first;
        while (first != second + 1) {
            tempSet.insert(*first++);
        }

        if (tempSet.size() == difference + 1) return ++second;
        tempSet.clear();
        first = ++tempFirst;
        second++;
    }

    return end;
}