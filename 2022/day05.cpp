#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <deque>
#include <iterator>

struct moveCommand {
    uint32_t number, origin, destination;
};

moveCommand createCommand(const std::string& commandString);
void runCommandOne(std::vector<std::deque<char>>& crateStack, const moveCommand& command);
void runCommandTwo(std::vector<std::deque<char>>& crateStack, const moveCommand& command);
std::ostream& printResult(std::ostream& output, std::vector<std::deque<char>>& crateStack);

int main(void) {
    std::vector<std::string> tempCrateRow;
    std::vector<moveCommand> moveCommands;
    std::deque<uint32_t> columns;
    std::string inputString;

    uint32_t inputState = 0;

    while (std::getline(std::cin, inputString)) {
        if (inputString.length() == 0) {
            tempCrateRow.pop_back();
            inputState ++;
        }
        if (!inputState) {  // input into crateStack
            tempCrateRow.push_back(inputString);
        }
        else {              // input into moveCommands
            if (inputString.length()) moveCommands.push_back(createCommand(inputString));
        }
    }

    // Grab the index of each of the values we need
    int32_t i = tempCrateRow[0].length() - 2;
    while (i > 0 ) {
        columns.push_front(i);
        i -= 4;
    }
    i = 0;

    std::vector<std::deque<char>> crateStack(columns.size());
    for (auto it = tempCrateRow.rbegin(); it != tempCrateRow.rend(); it++) { // For each row starting at the bottom, grab the contents of the string and add it to the stack
        do {
            if ((*it)[columns[i]] != ' ') crateStack[i].push_front((*it)[columns[i]]);
        } while (++i < crateStack.size());
        i = 0;
    }

    std::vector<std::deque<char>> crateStackTwo(crateStack); // Make a copy of the original queue for use in part two

    for (const auto& command : moveCommands) {
        runCommandOne(crateStack, command);
        runCommandTwo(crateStackTwo, command);
    }

    std::cout << "Part One:" << std::endl;
    printResult(std::cout, crateStack) << std::endl;

    std::cout << "Part Two:" << std::endl;
    printResult(std::cout, crateStackTwo) << std::endl;

    return 0;
}

moveCommand createCommand(const std::string& commandString) {
    moveCommand command;

    std::size_t move = commandString.find("move");
    std::size_t from = commandString.find("from");
    std::size_t to = commandString.find("to");

    command.number = std::stoi(commandString.substr(move + 4,3));
    command.origin = std::stoi(commandString.substr(from + 4,3));
    command.destination = std::stoi(commandString.substr(to + 2,3));

    return command;
}

void runCommandOne(std::vector<std::deque<char>>& crateStack, const moveCommand& command) {
    for (uint32_t it = 0; it < command.number; it++) {
        crateStack[command.destination - 1].push_front(crateStack[command.origin - 1].front());
        crateStack[command.origin - 1].pop_front();
    }
}

void runCommandTwo(std::vector<std::deque<char>>& crateStack, const moveCommand& command) {
    std::deque<char> tempQueue;
    for (uint32_t it = 0; it < command.number; it++) {
        tempQueue.push_back(crateStack[command.origin - 1].front());
        crateStack[command.origin - 1].pop_front();
    }

    for (auto it = tempQueue.rbegin(); it != tempQueue.rend(); it++) {
        crateStack[command.destination - 1].push_front(*it);
    }
}

std::ostream& printResult(std::ostream& output, std::vector<std::deque<char>>& crateStack) {
    for (const auto& front : crateStack) {
        output << front.front();
    }
    return output;
}