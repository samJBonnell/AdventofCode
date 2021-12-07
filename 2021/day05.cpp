#include <iostream>
#include <map>
#include <utility>
#include <regex>
#include <sstream>
#include <string>
#include <array>

#include "day05.hpp"

int main(void) {
    typedef std::vector<std::vector<uint16_t>> seaVec;

    std::vector<line> thermalVents;
    std::string tempStr;
    std::array<uint16_t, 4> tempArr;

    std::string regexPattern("[0-9]+");
    std::regex reg(regexPattern, std::regex::icase);

    uint16_t index = 0;
    uint16_t max_x = 0;
    uint16_t max_y = 0;

    while (std::getline(std::cin, tempStr)) {
        for (std::sregex_iterator it(tempStr.begin(), tempStr.end(), reg), end_it; it != end_it && index < 4; it++) {
            uint16_t strNum = std::stoi(it->str());
            tempArr[index++] = strNum;
        }
        thermalVents.push_back(line(tempArr[0], tempArr[2], tempArr[1], tempArr[3]));
        max_x = (std::max(tempArr[2], tempArr[0]) > max_x) ? std::max(tempArr[2], tempArr[0]) : max_x;
        max_y = (std::max(tempArr[3], tempArr[1]) > max_y) ? std::max(tempArr[3], tempArr[1]) : max_y;

        index = 0;
    }

    seaVec sea_floor(max_y + 1, std::vector<uint16_t>(max_x + 1, 0));

    for (auto& vent : thermalVents) {
        //if (vent.VandH()) vent.addPos(sea_floor);   // Part One
        vent.addPos(sea_floor);                   // Part Two
    }

    uint16_t intersectionPoints = 0;

    for (auto it_one = sea_floor.begin(); it_one != sea_floor.end(); it_one++) {
        for (auto it_two = it_one->begin(); it_two != it_one->end(); it_two++) {
            if (*it_two >= 2) intersectionPoints++;
        }
    }

    std::cout << intersectionPoints << std::endl;

    return 0;
}