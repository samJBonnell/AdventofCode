#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <iterator>

std::set<char> set_intersection(std::set<char>&, std::set<char>&);

struct RuckSack {
    std::set<char> front, back;
};

int main(void) {
    std::vector<RuckSack> RuckSacks;
    std::string inputString, front, back;
    RuckSack tempSack;

    while (std::getline(std::cin, inputString)) {
        front = inputString.substr(0, inputString.length()/2);
        back = inputString.substr(inputString.length()/2);

        for (uint16_t i = 0; i < front.length(); i++) {
            tempSack.front.insert(front[i]);
            tempSack.back.insert(front[i]);
        }

        RuckSacks.push_back(tempSack);
    }

    for (const auto& sack : RuckSacks) {
        
    }

    return 0;
}

std::set<char> set_intersection(std::set<char>& front, std::set<char>& back) {
    std::set<char> tempSet;
    for (auto item = front.begin(); item != front.end(); item++) {
        if (back.find(*item) != back.end()) tempSet.insert(*item);
    }

    return tempSet;
}