#include <iostream>
#include <vector>
#include <string>
#include <iterator>

const uint32_t UPPERFACTOR = 38;
const uint32_t LOWERFACTOR = 96;

void uniqueChars(std::string& inputSet, const std::string& front);

struct RuckSack {
    std::string front, back;
};

int main(void) {
    std::vector<RuckSack> RuckSacks;
    RuckSack tempSack;

    std::string inputString, front, back, tempString;
    uint32_t score = 0;

    while (std::getline(std::cin, inputString)) {
        front = inputString.substr(0, inputString.length()/2);
        back = inputString.substr(inputString.length()/2);

        for (uint16_t i = 0; i < front.length(); i++) {
            tempSack.front.push_back(front[i]);
            tempSack.back.push_back(back[i]);
        }

        RuckSacks.push_back(tempSack);
    }

    for (const auto& sack : RuckSacks) {
        uniqueChars(tempString, sack.front);
        if (std::isupper(*tempString.begin())) score += *tempString.begin() - UPPERFACTOR;
        else score += *tempString.begin() - LOWERFACTOR;
        tempString.clear();
    }

    std::cout << "Part One;" << std::endl << score << std::endl;

    return 0;
}

void uniqueChars(std::string& inputString, const std::string& front) {
    for (const auto& character : front) {
        if (front.find(character) == std::string::npos) inputString.push_back(character);
    }
}