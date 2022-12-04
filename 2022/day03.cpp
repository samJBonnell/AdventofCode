#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <set>

const uint32_t UPPERFACTOR = 38;
const uint32_t LOWERFACTOR = 96;

void uniqueChars(char& returnChar, const std::set<char> front, const std::set<char> back);
void commonSet(std::set<char>& returnSet, const std::set<char>& front, const std::set<char>& back);

struct RuckSack {
    std::set<char> front, back;
    std::set<char> total;
};

int main(void) {
    std::vector<RuckSack> RuckSacks;
    RuckSack tempSack;

    std::string inputString, front, back;
    uint32_t score = 0;
    char tempChar;

    while (std::getline(std::cin, inputString)) {
        front = inputString.substr(0, inputString.length()/2);
        back = inputString.substr(inputString.length()/2);

        for (const auto& character : inputString) {
            tempSack.total.insert(character);
        }

        for (uint16_t i = 0; i < front.length(); i++) {
            tempSack.front.insert(front[i]);
            tempSack.back.insert(back[i]);
        }

        RuckSacks.push_back(tempSack);
        tempSack.front.clear();
        tempSack.back.clear();
        tempSack.total.clear();
    }

    // Part One
    for (const auto& sack : RuckSacks) {
        uniqueChars(tempChar, sack.front, sack.back);
        if (std::isupper(tempChar)) score += tempChar - UPPERFACTOR;
        else score += tempChar - LOWERFACTOR;
    }

    // Part Two
    std::set<char> tempSet;
    uint32_t score2 = 0;

    for (auto sack = RuckSacks.begin(); sack != RuckSacks.end(); sack + 3) {
        commonSet(tempSet, (*(sack++)).total, (*(sack++)).total);
        commonSet(tempSet, (*(sack++)).total, tempSet);

        if (std::isupper(*tempSet.begin())) score2 += *tempSet.begin() - UPPERFACTOR;
        else score2 += *tempSet.begin() - LOWERFACTOR;

        tempSet.clear();
    }

    std::cout << "Part One;" << std::endl << score << std::endl;
    std::cout << "Part Two;" << std::endl << score2 << std::endl;

    return 0;
}

void uniqueChars(char& returnChar, const std::set<char> front, const std::set<char> back) {
    for (const auto& item : front) {
        if (back.find(item) != back.end()) returnChar = item;
    }
}

void commonSet(std::set<char>& returnSet, const std::set<char>& front, const std::set<char>& back) {
    for (const auto& item : front) {
        if (back.find(item) != back.end()) returnSet.insert(item);
    }
}