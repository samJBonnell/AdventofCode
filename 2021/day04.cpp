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
    std::string tempChar;

    std::getline(std::cin, tempStr);
    std::stringstream tempStream(tempStr);
    while (std::getline(tempStream, tempChar, ',')) {
        randomNumbers.push_back(std::stoi(tempChar));
    }
    std::cin.clear();
    

    while (!std::cin.eof()) {
        boards.push_back(BingoBoard(std::cin));
    }
    boards.erase(boards.begin());

    // Part One

    std::set<uint16_t> calledNumbers;
    std::vector<uint16_t>::iterator nextNum = randomNumbers.begin();
    
    bool solved = 0;
    auto it = boards.begin();

    do {
        it = boards.begin();
        calledNumbers.insert(*(nextNum++));

        for (; it != boards.end() && !solved; it++) {
            solved = it->checkBoard(calledNumbers);
        }
    } while (!solved && nextNum != randomNumbers.end());

    uint16_t uncalledSumOne = (--it)->sumNotFound(calledNumbers);
    uint16_t lastCalledOne = *(nextNum - 1);

    // Part Two

    it->resetBoard();

    nextNum = randomNumbers.begin();
    calledNumbers.clear();

    uint16_t solvedSum = 0;

    do {
        it = boards.begin();
        calledNumbers.insert(*(nextNum++));

        for (;it != boards.end() && solvedSum != boards.size(); it++) {
            solvedSum += it->checkBoard(calledNumbers);
        }
    } while (solvedSum != boards.size() && nextNum != randomNumbers.end());

    uint16_t uncalledSumTwo = (--it)->sumNotFound(calledNumbers);
    uint16_t lastCalledTwo = *(nextNum - 1);

    std::cout << "Part One:" << std::endl << uncalledSumOne << " " << lastCalledOne << std::endl << uncalledSumOne * lastCalledOne << std::endl;
    std::cout << std::endl;
    std::cout << "Part Two:" << std::endl << uncalledSumTwo << " " << lastCalledTwo << std::endl << uncalledSumTwo * lastCalledTwo << std::endl;

    return 0;
}