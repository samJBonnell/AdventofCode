#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct shiftRange {
    uint32_t begin, end;
};

struct shiftComparison {
    shiftRange first, second;
};

uint32_t compareShifts(const shiftComparison& shifts);
uint32_t overlappingShifts(const shiftComparison& shifts);

int main(void) {
    std::vector<shiftComparison> shifts;
    std::string inputString;

    shiftRange tempRange;
    shiftComparison tempComp;

    uint32_t index = 0;
    uint32_t containedShifts = 0;
    uint32_t overlappingShiftsScore = 0;

    while (std::getline(std::cin, inputString, ',')) { // Split all fo the inputs on the comma
        std::stringstream tempStream(inputString);
        while (std::getline(tempStream, inputString, '\n')) {
            std::size_t division = inputString.find("-");
            tempRange.begin = std::stoi(inputString.substr(0,division));
            tempRange.end = std::stoi(inputString.substr(division + 1,inputString.length()));
            if (index++ == 0) tempComp.first = tempRange;
            else {
                index = 0;
                tempComp.second = tempRange;
                shifts.push_back(tempComp);
            }
        }
    }

    for (const auto& shiftComp : shifts) {
        containedShifts += compareShifts(shiftComp);
        overlappingShiftsScore += overlappingShifts(shiftComp);
    }

    std::cout << "Part One:" << std::endl << containedShifts << std::endl;
    std::cout << "Part Two:" << std::endl << overlappingShiftsScore << std::endl;

    return 0;
}

uint32_t compareShifts(const shiftComparison& shifts) {
    uint32_t tempBool = 0;
    if (shifts.first.begin >= shifts.second.begin) {
        if (shifts.second.end >= shifts.first.end) tempBool = 1;
    }
    if (shifts.second.begin >= shifts.first.begin) {
        if (shifts.first.end >= shifts.second.end) tempBool = 1;
    }

    return tempBool;
}

uint32_t overlappingShifts(const shiftComparison& shifts) {
    uint32_t tempBool = 0;
    
    if (shifts.first.begin <= shifts.second.begin) {
        if (shifts.second.begin <= shifts.first.end) tempBool = 1;
    }
    if (shifts.second.begin <= shifts.first.begin) {
        if (shifts.first.begin <= shifts.second.end) tempBool = 1;
    }

    return tempBool;
}