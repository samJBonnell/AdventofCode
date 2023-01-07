#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <vector>

#include "day11.hpp"

constexpr uint32_t ROUNDS = 10000;

int main(void) {
    std::vector<Monkey> monkeys;
    Monkey monkeyTemp;

    std::string stringInput;
    uint32_t a = std::stoi(" 2");
    
    while (std::getline(std::cin, stringInput)) {
        if (stringInput.find("Monkey") != std::string::npos) monkeyTemp.setIdentifier(std::stoi(stringInput.substr(7, stringInput.size() - 8)));
        else if (stringInput.find("Starting items:") != std::string::npos) {
            std::stringstream sstreamTemp(stringInput.substr(17));
            while (std::getline(sstreamTemp, stringInput, ',')) {
                monkeyTemp.addItems().push_back(std::stoi(stringInput));
            }
        }
        else if (stringInput.find("Operation:") != std::string::npos) {
            monkeyTemp.setModifier() = stringInput.substr(23)[0];
            std::string magnitude = stringInput.substr(25);
            if (is_number(magnitude)) monkeyTemp.setMagnitude(std::stoi(magnitude));
            else monkeyTemp.setOperatingMode(true);
        }
        else if (stringInput.find("Test:") != std::string::npos) {
            std::string magnitude = stringInput.substr(21);
            monkeyTemp.setTestMagnitude(std::stoi(magnitude));
        }
        else if (stringInput.find("If true") != std::string::npos) {
            std::string index = stringInput.substr(29);
            monkeyTemp.setTrueMonkey(std::stoi(index));
        }
        else if (stringInput.find("If false") != std::string::npos) {
            std::string index = stringInput.substr(30);
            monkeyTemp.setFalseMonkey(std::stoi(index));
        }
        else if (stringInput == "")  {
            monkeys.push_back(monkeyTemp);
            monkeyTemp.clear();
        }
    }
    monkeys.push_back(monkeyTemp);

    uint64_t modulusValue = 1;
    for (auto& ptr : monkeys) {
        modulusValue *= ptr.returnTestValue();
    }

    for (auto& ptr : monkeys) { ptr.setModulusValue(modulusValue); }

    for (uint32_t round = 0; round < ROUNDS; round++) {
        for (auto& ptr : monkeys) {
            while (ptr.itemSize() > 0) {
                ptr.updateWorryLevel();
                ptr.passItem(monkeys);
            }
        }
        /*
        std::cout << "Round: " << round << std::endl;
        for (auto& ptr : monkeys) {
            ptr.print();
        }
        std::cout << std::endl;
        */
    }

    uint32_t max = 0, second = 0;
    for (auto& ptr : monkeys) {
        if (max < ptr.returnNumberOfHandledItems()) {
            second = max;
            max = ptr.returnNumberOfHandledItems();
        }
    }

    uint32_t monkeyBusiness = max * second;
    std::cout << monkeyBusiness << std::endl;

    return 0 ;
}