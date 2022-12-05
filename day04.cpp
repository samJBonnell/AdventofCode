#include <iostream>
#include <string>
#include <vector>

struct shiftRange {
    uint32_t begin, end;
};

struct shiftComparison {
    shiftRange first, second;
};

int main(void) {
    std::vector<shiftComparison> shifts;
    std::string inputString;

    shiftRange tempRange;
    shiftComparison tempComp;

    uint32_t index = 0;

    while (std::getline(std::cin, inputString, ',')) { // Split all fo the inputs on the comma
        std::size_t division = inputString.find("-");
        tempRange.begin = std::stoi(inputString.substr(0,division));
        tempRange.end = std::stoi(inputString.substr(division,inputString.length()));
        if (!index++) tempComp.first = tempRange;
        else {
            index = 0;
            tempComp.second = tempRange;
        }
    }

    return 0;
}