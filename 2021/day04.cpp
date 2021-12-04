#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include <sstream>

#include "day04.h"

int main(void) {
    std::vector<BingoBoard> boards;
    std::vector<uint16_t> randomNumbers;

    std::string tempStr;

    while (!std::cin.eof()) {
        boards.push_back(BingoBoard(std::cin));
    }
    std::cin.clear();

    while (std::getline(std::cin, tempStr, ',')) randomNumbers.push_back(std::stoi(tempStr));

    std::set<uint16_t> calledNumbers;
    std::vector<uint16_t>::iterator nextNum = randomNumbers.begin();
    
    bool solved = 0;
    auto it = boards.begin();

    do {
        it = boards.begin();
        calledNumbers.insert(*(nextNum++));
        for (; it != boards.end(); it++) {
            solved = it->checkBoard(calledNumbers);
        }
    } while (!solved && nextNum != randomNumbers.end());

    uint16_t uncalledSum = (--it)->sumNotFound(calledNumbers);
    uint16_t lastCalled = *(--nextNum);

    std::cout << uncalledSum << " " << lastCalled << std::endl << uncalledSum * lastCalled << std::endl;

    return 0;
}