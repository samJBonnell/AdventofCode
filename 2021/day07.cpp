#include <iostream>
#include <string>
#include <algorithm>
#include <set>

uint32_t fuel_for_move(const uint16_t& rhs, const uint16_t& lhs);

int main(void) {
    std::multiset<uint16_t> crabmarines;
    std::set<uint16_t>      possibleLocations;

    std::string tempStr;

    while (std::getline(std::cin, tempStr, ',')) crabmarines.insert(std::stoi(tempStr));    // Add all crab locations to index
    uint32_t minLocation = *crabmarines.begin(), maxLocation = *crabmarines.rbegin();
    while (minLocation <= maxLocation) possibleLocations.insert(minLocation++);

    uint64_t consumed_fuel = 0;
    uint64_t current_fuel_consumption = 0;

    for (const auto& location : possibleLocations) {
        for (const auto& ref : crabmarines) {
            current_fuel_consumption += fuel_for_move(ref, location);
        }
        if (!consumed_fuel) consumed_fuel = current_fuel_consumption;
        consumed_fuel = (current_fuel_consumption < consumed_fuel) ? current_fuel_consumption : consumed_fuel;
        current_fuel_consumption = 0;
    }

    std::cout << consumed_fuel << std::endl;

    return 0;
}

uint32_t fuel_for_move(const uint16_t& rhs, const uint16_t& lhs) {
    uint32_t total_fuel = 0;
    int dist = std::abs(lhs - rhs);
    /*while (distance != 0) {
        total_fuel += distance--;
    }*/

    return dist * (dist - 1) / 2;
}