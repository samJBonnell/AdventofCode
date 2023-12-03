#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>

int main(void) {
    std::set<uint32_t> elfCalories;
    std::string calorie;
    uint32_t currentCalories = 0;

    auto start = std::chrono::high_resolution_clock::now();
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
    
    auto stop = std::chrono::high_resolution_clock::now();   
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << std::endl;
    return 0;
}