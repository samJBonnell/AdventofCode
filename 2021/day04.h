#ifndef DAY04_H
#define DAY04_H

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

class BingoBoard {
public:
    BingoBoard() = default;
    BingoBoard(std::istream& in);

    bool checkBoard(const std::set<uint16_t>& winningNumbers);
    void printBoard(std::ostream& out) const;
    uint16_t sumNotFound(std::set<uint16_t>& calledNumbers) const;

private:
    std::map<uint16_t, uint16_t> board;
};

BingoBoard::BingoBoard(std::istream& in) {
    std::string tempStr;
    uint16_t index = 0;
    char tempChar;

    while (index < 25 && !in.eof()) {
        in >> tempStr;
        board.insert(std::pair<uint16_t, uint16_t>(std::stoi(tempStr), index++));
    }

    return;
}

bool BingoBoard::checkBoard(const std::set<uint16_t>& winningNumbers) {
    std::set<uint16_t> indexes;
    uint16_t sequence = 0;

    for (const auto& winningNumber : winningNumbers) {
        auto it = board.find(winningNumber);
        if (it != board.end()) indexes.insert(it->second);
    }

    auto first = indexes.begin(), second = indexes.begin();
    second++;

    for (; second != indexes.end(); first++, second++) {
        if (*(first) + 1 == *second || *(first) - 1 == *second || *(first) + 5 == *second || *(first) - 5 == *second) {
            sequence += 1;
        }
        else {
            sequence = 0;
        }
    }
    
    return (sequence >= 5);
}

uint16_t BingoBoard::sumNotFound(std::set<uint16_t>& calledNumbers) const {
    uint16_t uncalledSum = 0;
    for (const auto& value : board) {
        uncalledSum += value.first;
    }

    for (const auto& number : calledNumbers) {
        auto it = board.find(number);
        if (it != board.end()) uncalledSum -= number;
    }

    return uncalledSum;
}

#endif // DAY04_H