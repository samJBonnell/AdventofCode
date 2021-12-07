#ifndef DAY05_HPP
#define DAY05_HPP

#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>

typedef std::vector<std::vector<uint16_t>> seaVec;

class line {
public:

    line() = default;
    line(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2);

    bool VandH() const;
    void addPos(seaVec& sea_floor);

    friend bool operator==(const line& lhs, const line& rhs);

private:
    std::pair<uint16_t, uint16_t> x;
    std::pair<uint16_t, uint16_t> y;

    std::multimap<uint16_t, uint16_t> linePoints;
};

line::line(const uint16_t& x1, const uint16_t& x2, const uint16_t& y1, const uint16_t& y2) {
    x.first = x1;
    x.second = x2;
    y.first = y1;
    y.second = y2;

    uint16_t it_x = std::min(x.first, x.second);
    uint16_t x_end = std::max(x.first, x.second);
    uint16_t it_y = std::min(y.first, y.second);
    uint16_t y_end = std::max(y.first, y.second);

    int slope;
    int b;

    if (x.second - x.first) {
        slope = static_cast<double>(y.second - y.first)/(x.second - x.first);
        b = y.second - slope * x.second;
        while (it_x <= x_end) {
            it_y = slope * it_x + b;
            linePoints.insert(std::pair<uint16_t, uint16_t>(it_x++, it_y));
        }
    }
    else {
        while (it_y <= y_end) {
            linePoints.insert(std::pair<uint16_t, uint16_t>(it_x, it_y++));
        }
    }

    return;
}

bool operator==(const line& lhs, const line& rhs) {
    if (lhs.x == rhs.x && lhs.y == rhs.y) return 1;
    return 0;
}

bool line::VandH() const {
    if (x.first == x.second || y.first == y.second) return 1;
    return 0;
}

void line::addPos(seaVec& sea_floor) {
    for (const auto& point : linePoints) {
        sea_floor[point.second][point.first]++;
    }
}

#endif // DAY05_HPP