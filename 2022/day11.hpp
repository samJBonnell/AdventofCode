#ifndef DAY_11
#define DAY_11

#include <deque>
#include <functional>
#include <algorithm>
#include <cctype>
#include <cmath>

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

struct Worry {
    uint64_t oldWorry;
    uint64_t modifier;

    uint32_t mode;
};

class Monkey {
public:
    Monkey() = default;
    Monkey(std::deque<uint64_t>& iniItems) : items(iniItems) {};

    inline void clear() {
        items.clear();

        identifier = 0;
        monkeyTrue = 0;
        monkeyFalse = 0;

        numberOfViewedItems = 0;

        modifier = '0';
        operatingMode = false;
        magnitude = 0;
        testMagnitude = 0;
    }

    inline void setIdentifier(const uint32_t& id) { identifier = id; }
    inline void setItems(const std::deque<uint64_t>& iniItems) { items = iniItems; }
    inline std::deque<uint64_t>& addItems() { return items; }
    inline void setMagnitude(const uint64_t iniMagnitude) { magnitude = iniMagnitude; }
    inline void setOperatingMode(const bool iniState) { operatingMode = iniState; }
    inline void setTestMagnitude(const uint64_t iniMagnitude) { testMagnitude = iniMagnitude; }
    inline void setTrueMonkey(const uint64_t index) { monkeyTrue = index; }
    inline void setFalseMonkey(const uint64_t index) { monkeyFalse = index; }
    inline char& setModifier() { return modifier; }
    inline void setModulusValue(const uint64_t iniValue) { modulusValue = iniValue; }

    inline uint32_t itemSize() { return items.size(); }
    inline uint32_t returnNumberOfHandledItems() { return numberOfViewedItems; }
    inline uint64_t returnTestValue() { return testMagnitude; }

    void updateWorryLevel();
    void passItem(std::vector<Monkey>& monkeys);
    void print();


private:
    uint32_t identifier;
    uint32_t monkeyTrue;
    uint32_t monkeyFalse;

    uint64_t numberOfViewedItems = 0;

    char modifier;
    bool operatingMode = false;
    uint64_t magnitude;
    uint64_t testMagnitude;

    std::deque<uint64_t> items;
    const uint32_t boredModifier = 1;
    uint64_t modulusValue;
};

void Monkey::updateWorryLevel() {
    uint64_t intTemp = items.front();
    uint64_t magnitudeTemp = (operatingMode) ? items.front() : magnitude;

    switch (modifier) {
        case '+':
            intTemp += magnitudeTemp;
            break;
        case '-':
            intTemp -= magnitudeTemp;
            break;
        case '*':
            intTemp *= magnitudeTemp;
            break;
        default:
            break;
    }

    items.front() = std::floor((double)intTemp / boredModifier);
    items.front() = intTemp % (modulusValue );
    return;
}

void Monkey::passItem(std::vector<Monkey>& monkeys) {
    if (!(items.front() % testMagnitude)) monkeys[monkeyTrue].addItems().push_back(items.front());
    else monkeys[monkeyFalse].addItems().push_back(items.front());
    numberOfViewedItems++;
    items.pop_front();
}

void Monkey::print() {
    std::cout << "Monkey: " << identifier << " - ";
    for (const auto& ptr : items) std::cout << ptr << " ";
    std::cout << std::endl;
}

#endif