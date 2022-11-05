#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cstdint>
#include <set>
#include <utility>

bool check_adjacent(const std::multiset<uint16_t>& heights, const uint16_t& target);
std::multiset<uint16_t> make_adjacent(const std::vector<std::vector<uint16_t>>& cave_floor, const uint16_t& row, const uint16_t& col);
bool check_set(std::multiset<uint16_t>::iterator& it, std::multiset<uint16_t>::iterator& end, const uint16_t& target);
uint16_t basin_size(std::vector<std::vector<uint16_t>>& cave_floor, uint16_t it_row, uint16_t it_col, std::set<std::pair<uint16_t, uint16_t>>& basin_points);

int main(void) {
    std::vector<std::vector<uint16_t>> cave_floor;
    std::vector<uint16_t> tempVec;
    std::string tempStr;

    uint64_t total_risk = 0;
    uint64_t basin_area = 0;

    std::set<std::pair<uint16_t, uint16_t>> low_points;

    while (std::getline(std::cin, tempStr)) {
        tempVec.push_back(9);
        for (auto it = tempStr.begin(), eos = tempStr.end(); it != eos; it++) tempVec.push_back(*it - '0');
        tempVec.push_back(9);
        cave_floor.push_back(tempVec);
        tempVec.clear();
    }

    size_t cave_width = cave_floor[0].size();
    std::vector<uint16_t> paddingVec(cave_width, 9);
    cave_floor.insert(cave_floor.begin(), paddingVec);
    cave_floor.push_back(paddingVec);

    // Part One

    for (uint16_t it_row = 1; it_row < cave_floor.size() - 1; it_row++) {
        for (uint16_t it_col = 1; it_col < cave_floor[it_row].size() - 1; it_col++) {
            if (check_adjacent(make_adjacent(cave_floor, it_row, it_col), cave_floor[it_row][it_col])) { 
                total_risk += cave_floor[it_row][it_col] + 1;
                low_points.insert(std::pair<uint16_t, uint16_t>(it_row, it_col));
            }
        }
    }

    // Part Two



    std::cout << "Part One:" << std::endl << total_risk << std::endl;
    std::cout << "Part Two:" << std::endl << basin_area << std::endl;

    return 0;
}

bool check_adjacent(const std::multiset<uint16_t>& heights, const uint16_t& target) {
    auto it = heights.begin(), end = heights.end();
    if (*it++ == target && check_set(it, end, target)) return 1;
    return 0;
}

bool check_set(std::multiset<uint16_t>::iterator& it, std::multiset<uint16_t>::iterator& end, const uint16_t& target) {
    while (it != end) {
        if (*it++ == target) return 0;
    }

    return 1;
}

std::multiset<uint16_t> make_adjacent(const std::vector<std::vector<uint16_t>>& cave_floor, const uint16_t& row, const uint16_t& col) {
    std::multiset<uint16_t> tempSet;

    for (int i = -1; i < 2; i++) tempSet.insert(cave_floor[row + i][col]); // Get the rows
    for (int i = -1; i < 2; i+= 2) tempSet.insert(cave_floor[row][col + i]); // Get the cols

    return tempSet;
}

uint16_t basin_size(std::vector<std::vector<uint16_t>>& cave_floor, uint16_t it_row, uint16_t it_col, std::set<std::pair<uint16_t, uint16_t>>& basin_points) {
    
}