#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <functional>

// Need to check the ends as well!
// Should only check 

bool checkSequence(std::vector<int>& report, std::function<bool(const int&, const int&, const int&, const int&)> compare, const int& lowerBound, const int& upperBound, const bool& programDamper) {
    std::vector<int>::iterator ptr = report.begin(), end = report.end();
    while ((ptr + 1) != end && compare(*ptr, *(ptr+1), lowerBound, upperBound)) ptr++;
    if ((ptr + 1) == end) return 1;
    return 0;
}

// bool checkSequence(std::vector<int>& report, std::function)

/*
5 1 2 3 4 5

Check the 'slope' of the sequence
1 - 5 = -4
2 - 1 = 1
3 - 2 = 1
4 - 3 = 1
5 - 4 = 1

Remove the element with the incorrect slope?

7 6 4 2 1

6 - 7 = -1
4 - 6 = -2
2 - 4 = -2
1 - 2 = -1

Passes descending

1 2 7 8 9

2 - 1 = 1
7 - 2 = 5
7 - 8 = 1
9 - 8 = 1

Remove 7

2 - 1 = 1
8 - 2 = 1

Fails

Fails

Remove 

9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9

Ascending Check
1 2 3 4 9
2 - 1 = 1
3 - 2 = 1
4 - 3 = 1
9 - 4 = 5

-> Remove 9

9 1 2 3 4
1 - 9 = -8
2 - 1 = 1
3 - 2 = 1
4 - 3 = 1

-> Remove 9

If slope > && slope > max 0:
    Remove 2nd element
If slope < 0 && abs(slope) > max:
    Remove 1st element
If slope == 0:
    Remove 1st or 2nd element

5 4 3 2 1
4 - 5 = -1
3 - 4 = -1
2 - 3 = -1
1 - 2 = -1

9 5 4 3 2 1
5 - 9 = -4
4 - 5 = -1
3 - 4 = -1
2 - 3 = -1
1 - 2 = -1


*/

int main(int argc, char** argv) {
    bool programDamper = (bool)argv[0];
    const std::vector<const int> limits = {1, 3};

    std::vector<std::string> input;
    std::string inputString;
    while(std::getline(std::cin, inputString)) {
        input.push_back(inputString);
    }

    std::vector<std::vector<int>> reports;
    for (const auto& row : input) {
        std::stringstream tempStream(row);
        std::string tempString;
        std::vector<int> tempVec;

        while(std::getline(tempStream, tempString, ' ')) {
            tempVec.push_back(std::stoi(tempString));
        }   
        reports.push_back(tempVec);
    }

    uint32_t safeReports = 0;
    bool checkIncreasing = 0, checkDecreasing = 0;
    for (auto& report : reports) {
        checkDecreasing = (int)checkSequence(report, [](int lhs, int rhs, int low, int high) -> bool { return (lhs - rhs >= low && lhs - rhs <= high); }, limits[0], limits[1], programDamper);
        checkIncreasing = (int)checkSequence(report, [](int lhs, int rhs, int low, int high) -> bool { return (lhs - rhs <= -low && lhs - rhs >= -high); }, limits[0], limits[1], programDamper);
        safeReports += checkDecreasing + checkIncreasing;
    }

    std::cout << std::endl << std::endl << "Part One:" << std::endl;
    std::cout << safeReports << std::endl;

    // std::cout << std::endl;
    // std::cout << "Part Two: " << std::endl;
    // std::cout << similarityScore << std::endl;

    return 0;
}