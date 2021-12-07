#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "day06_naive.hpp"

int main(void) {
    std::vector<fish> fish_population;
    std::vector<fish> newFish;
    uint16_t simulated_days = 256;

    std::string tempStr;

    while (std::getline(std::cin, tempStr, ',')) { fish_population.push_back(fish(std::stoi(tempStr))); }

    while (simulated_days-- != 0) {
        for (auto& fish : fish_population) { // For each day
            if (fish.returnTimer() == 0) {
                fish.weeklyReset();
                newFish.emplace_back();
            }
            else {
                fish.dailyUpdate();
            }
        }
        fish_population.insert(fish_population.end(), newFish.begin(), newFish.end());
        newFish.clear();
    }

    std::cout << std::endl << fish_population.size() << std::endl;

    return 0;
}