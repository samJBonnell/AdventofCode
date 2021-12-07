#include <iostream>
#include <array>
#include <string>
#include <algorithm>

int main(void) {
    uint16_t simulated_days = 256;

    std::array<uint64_t, 9> fish_population;
    std::fill_n(fish_population.begin(), 9, 0);

    std::string tempStr;
    while (std::getline(std::cin, tempStr, ',')) { fish_population[std::stoi(tempStr)]++; }

    uint64_t tempStorage;

    while (simulated_days-- != 0) {
        tempStorage = fish_population[0];
        for (size_t index = 1; index < 9; index++) {
            fish_population[index - 1] = fish_population[index];
        }
        fish_population[6] += tempStorage;
        fish_population[8] = tempStorage;
    }

    uint64_t total_fish = 0;
    for (const auto& pop : fish_population) total_fish += pop;

    std::cout << total_fish << std::endl;

    return 0;
}