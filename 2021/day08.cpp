#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "day08.hpp"

constexpr uint16_t ONE      = 2;
constexpr uint16_t FOUR     = 4;
constexpr uint16_t SEVEN    = 3;
constexpr uint16_t EIGHT    = 7;

int main(void) {
    std::vector<std::vector<uniqueSignal>> digitalOutputs;
    std::vector<uniqueSignal> tempVec;
    std::string tempStr;

    while (std::getline(std::cin, tempStr)) {
        std::size_t delimiter = tempStr.find('|');
        std::stringstream uniqueSignalStream(tempStr.substr(0, delimiter));
        std::stringstream outputValueStream(tempStr.substr(delimiter + 2));

        while (uniqueSignalStream >> tempStr) {
            tempVec.emplace_back(tempStr);
            auto it = &tempVec.back();
            switch (it->setLength()) {
            case ONE:
                it->setNum(1);
                break;
            case FOUR:
                it->setNum(4);
                break;
            case SEVEN:
                it->setNum(7);
                break;
            case EIGHT:
                it->setNum(8);
                break;
            }
        }

        while (outputValueStream >> tempStr)  { 
            tempVec.emplace_back(tempStr);
            auto it = &tempVec.back();
            switch (it->setLength()) {
            case ONE:
                it->setNum(1);
                break;
            case FOUR:
                it->setNum(4);
                break;
            case SEVEN:
                it->setNum(7);
                break;
            case EIGHT:
                it->setNum(8);
                break;
            }
        }

        digitalOutputs.push_back(tempVec);
        tempVec.clear();
    }

    // Part One

    uint32_t unique_numbers = 0, tempNum = 0;

    for (const auto& line : digitalOutputs) {
        for (uint32_t index = 10; index < 14; index++) {
            switch(line[index].num()) {
            case 1:
                unique_numbers++;
                break;
            case 4:
                unique_numbers++;
                break;
            case 7:
                unique_numbers++;
                break;
            case 8:
                unique_numbers++;
                break;
            }
        }
    }

    // Part Two

    uint64_t totalSum = 0;

    for (auto& line : digitalOutputs) {
        auto it_one = std::find(line.begin(), line.end(), 1);
        auto it_four = std::find(line.begin(), line.end(), 4);

        uint16_t index = 10;
        uint16_t multiple = 1000;

        for (; index < 14; index++) {
            if (line[index].num() == 8) totalSum += 8 * multiple;
            if (line[index].num() == 7) totalSum += 7 * multiple;
            if (line[index].num() == 4) totalSum += 4 * multiple;
            if (line[index].num() == 1) totalSum += 1 * multiple;

            if (line[index].setLength() == 6) {
                if (includes_set(line[index], *it_one)) {
                    if (includes_count(line[index], *it_four) == 4) {
                        totalSum += 9 * multiple;
                    }
                    else {
                        totalSum += 0 * multiple;
                    }
                }
                else {              
                    totalSum += 6 * multiple;
                }
            }

            if (line[index].setLength() == 5) { 
                if (includes_set(line[index], *it_one)) {
                    totalSum += 3 * multiple;
                }
                else {
                    if (includes_count(line[index], *it_four) == 3) {
                        totalSum += 5 * multiple;
                    }
                    else {
                        totalSum += 2 * multiple;
                    }
                }
            }

            multiple /= 10;
        }

        std::cout << totalSum << std::endl;
    }

    std::cout << std::endl << "Part One:" << std::endl << unique_numbers << std::endl;
    std::cout << "Part Two:" << std::endl << totalSum << std::endl;

    return 0;
}