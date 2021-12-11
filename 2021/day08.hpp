#ifndef DAY08_HPP
#define DAY08_HPP

#include <cstdint>
#include <set>
#include <string>
#include <algorithm>

class uniqueSignal {
public:
    uniqueSignal(const std::string& iniSignal);

    inline uint16_t setLength() const { return signalConnections.size(); }
    inline void setNum(uint16_t numIni) { number = numIni; }
    inline uint16_t num() const { return number; }
    inline std::set<char> returnSignal() const { return signalConnections; }

    friend bool operator==(const uniqueSignal& lhs, const uniqueSignal& rhs);
    friend bool operator==(const uniqueSignal& lhs, const uint64_t i);
    friend bool includes_set(const uniqueSignal& lhs, const uniqueSignal& rhs);
    friend uint16_t includes_count(const uniqueSignal& lhs, const uniqueSignal& rhs);

private:
    std::set<char> signalConnections;
    uint16_t number = 10;
};

uniqueSignal::uniqueSignal(const std::string& iniSignal) {
    for (const auto& connection : iniSignal) signalConnections.insert(connection);
    return;
}

bool operator==(const uniqueSignal& lhs, const uniqueSignal& rhs) {
    return (lhs.number == rhs.number) ? 1 : 0;
}

bool operator==(const uniqueSignal& lhs, const uint64_t i) {
    return (lhs.number == i) ? 1 : 0;
}

bool includes_set(const uniqueSignal& lhs, const uniqueSignal& rhs) { // Ensure smaller set is on the rhs of the function call
    if (std::includes(lhs.signalConnections.begin(), lhs.signalConnections.end(), rhs.signalConnections.begin(), rhs.signalConnections.end())) return true;
    return false;
}

uint16_t includes_count(const uniqueSignal& lhs, const uniqueSignal& rhs) {
    uint16_t count = 0;

    auto min_it = (lhs.signalConnections.size() < rhs.signalConnections.size()) ? rhs.signalConnections.begin() : lhs.signalConnections.begin();
    auto max_it = (lhs.signalConnections.size() < rhs.signalConnections.size()) ? rhs.signalConnections.end() : lhs.signalConnections.end();
    auto fixedSet = (lhs.signalConnections.size() > rhs.signalConnections.size()) ? &rhs.signalConnections : &lhs.signalConnections;

    for (; min_it != max_it; min_it++) { count += fixedSet->count(*min_it); }

    return count;
}

#endif // DAY08_HPP