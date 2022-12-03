#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>

struct pos {
    int x = 0;
    int y = 0;
    int aim = 0;
};

void submarinePos(std::vector<std::string>& input, pos& position);

int main(void) {
    std::vector<std::string> input;
    std::string tempString;
    pos position;

    while (std::getline(std::cin, tempString)) { input.push_back(tempString); }
    submarinePos(input, position);

    std::cout << position.y * position.x << std::endl;

    return 0;
}

void submarinePos(std::vector<std::string>& input, pos& position) {
    std::string inputCommand;
    int modifier;
    
    for (const auto& line : input) {
        std::stringstream inputStr(line);
        inputStr >> inputCommand >> modifier;

        if (inputCommand == "forward")  { position.x += modifier; position.y += modifier * position.aim; }
        if (inputCommand == "up")       { position.aim -= modifier; }
        if (inputCommand == "down")     { position.aim += modifier; }
    }

    return;
}