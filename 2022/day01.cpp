#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <algorithm>

int main(void) {
    std::set<uint32_t> elfCalories;
    std::string calorie;
    uint32_t currentCalories = 0;

    while (std::getline(std::cin, calorie)) {
        if (calorie == "") {
            elfCalories.insert(currentCalories);
            currentCalories = 0;
        }
        else currentCalories += std::stoi(calorie);
    }

    elfCalories.insert(currentCalories);

    // Part One
    std::cout << "Part One:" << std::endl << *(elfCalories.rbegin()) << std::endl;

    // Part Two
    auto i = elfCalories.rbegin();
    uint32_t tripleSum = *(i++) + *(i++) + *i;
    std::cout << std::endl << "Part Two:" << std::endl << tripleSum << std::endl;
    return 0;
}