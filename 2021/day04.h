#ifndef DAY04_H
#define DAY04_H

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

class BingoBoard {
public:
    BingoBoard() = default;
    BingoBoard(std::istream& in);

    inline void resetBoard() { winState = 0; };

    bool checkBoard(const std::set<uint16_t>& winningNumbers);
    void printBoard(std::ostream& out) const;
    uint16_t sumNotFound(std::set<uint16_t>& calledNumbers) const;

    bool winState = 0;

private:
    std::vector<std::set<uint16_t>> winningConditions;
    std::array<std::set<uint16_t>, 5> rows, cols;
    uint16_t boardSum = 0;
};

BingoBoard::BingoBoard(std::istream& in) {
    uint16_t col_index = 0, row_index = 0, temp_int;
    std::string tempStr;

    while (std::getline(in, tempStr) && tempStr[0] != '\0') {
        std::stringstream tempStream(tempStr);
        while (tempStream >> tempStr) {
            temp_int = std::stoi(tempStr);
            cols[col_index++ % 5].insert(temp_int);
            rows[row_index % 5].insert(temp_int);
            boardSum += temp_int;
        }
        col_index = 0;
        row_index++;
    }

    for (const auto& row : rows) winningConditions.push_back(row);
    for (const auto& col : cols) winningConditions.push_back(col);

    return;
}

bool BingoBoard::checkBoard(const std::set<uint16_t>& calledNumbers){
    std::set<uint16_t>::iterator it = calledNumbers.begin(), end = calledNumbers.end();

    if (winState) return 0;

    for (const auto& winningCondition : winningConditions) {
        if (std::includes(it, end, winningCondition.begin(), winningCondition.end())) {
            winState = 1;
            return 1;
        }
    }

    return 0;
}

uint16_t BingoBoard::sumNotFound(std::set<uint16_t>& calledNumbers) const {
    uint16_t subtractiveSum = 0;
    for (const auto& number : calledNumbers) {
        for (const auto& row : rows) {
            if (row.find(number) != row.end()) subtractiveSum += number;
        }
    }
    return (boardSum - subtractiveSum);
}

#endif // DAY04_H