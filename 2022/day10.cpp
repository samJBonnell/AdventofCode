#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <deque>

struct registerState {
    uint32_t iteration;
    int32_t registerSize;

    registerState() = default;
    registerState(const uint32_t& iniIteration, const int32_t& iniRegisterSize) : iteration(iniIteration), registerSize(iniRegisterSize) {};
};

void calculateScreen(std::vector<std::vector<char>>& CRT, std::deque<registerState>& iterationStates, const uint32_t& width);
void printScreen(const std::vector<std::vector<char>>& CRT);

int main(void) {
    std::istream_iterator<std::string> in(std::cin), eof;
    std::vector<std::string> inputCommands(in, eof);

    std::deque<registerState> iterationStates;
    uint32_t iteration = 0;
    int32_t globalRegister = 1;

    bool index = false;
    for (const auto& line : inputCommands) {
        if (!index) {
            if (line == "noop") {
                index = false;
                iteration++;

                registerState newState(iteration, globalRegister);
                iterationStates.push_back(newState);
            }
            else index = true;
        }
        else {
            for (uint32_t it = 0; it < 2; it++) {
                iteration++;
                registerState newState(iteration, globalRegister);
                iterationStates.push_back(newState);
            }

            int32_t size = std::stoi(line);
            globalRegister += size;

            index = false;
        }
    }

    int32_t partOne = 0;
    for (uint32_t it = 20; it <= 220; it += 40) partOne += it * iterationStates[it - 1].registerSize;
    std::cout << "Part One: " << partOne << std::endl;

    std::vector<std::vector<char>> CRT;
    calculateScreen(CRT, iterationStates, 40);
    printScreen(CRT);

    return 0;
}

void calculateScreen(std::vector<std::vector<char>>& CRT, std::deque<registerState>& iterationStates, const uint32_t& width) {
    std::vector<char> row;
    int32_t rowIndex = 0;
    char drawChar;

    for (const auto& state : iterationStates) {
        if (rowIndex == width) {
            CRT.push_back(row);
            row.clear();
            rowIndex = 0;
        }

        drawChar = (state.registerSize - 2 < rowIndex && rowIndex < state.registerSize + 2) ? '#' : '.';
        row.push_back(drawChar);
        rowIndex++;
    }

    CRT.push_back(row);

    return;
}

void printScreen(const std::vector<std::vector<char>>& CRT) {
    for (const auto& row : CRT) {
        for (const auto& point : row) std::cout << point;
        std::cout << std::endl;
    }

    return;
}