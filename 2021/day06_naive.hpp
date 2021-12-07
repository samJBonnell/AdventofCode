#ifndef DAY06_HPP
#define DAY06_HPP

#include <iostream> // To include uint16_t type

class fish {
public:
    fish(uint16_t override_timer = 8) : internal_timer(override_timer) {};

    inline void weeklyReset() { internal_timer = 6; };
    inline uint16_t returnTimer() const { return internal_timer; }
    inline void dailyUpdate() { internal_timer--; };

private:
    uint16_t internal_timer;
};


#endif // DAY06_HPP