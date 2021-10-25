#ifndef DAY11_H
#define DAY11_H

#include <iostream>
#include <string>
#include <vector>
#include <array>

class Seat {
public:
    Seat() = default;

    void queueUpdate(std::array<Seat, 8>& adjacentSeats);
    bool returnState(void) const { return (_State == '#') ? 1 : 0; }; // If the seat is occupied, return 1, else, return 0;
    void updateState();
    
    static void nextStep(void) {

    };

private:
    char _State;
    char _NextState;

    uint8_t     _numberofadjacentSeats = 0;

};

void Seat::queueUpdate(std::array<Seat, 8>& adjacentSeats) {
    for (const auto& seats : adjacentSeats) { this->_numberofadjacentSeats += seats.returnState(); }
    if  (this->_numberofadjacentSeats >= 4) this->_NextState = 'L';
    if  (!this->_numberofadjacentSeats)     this->_NextState = '#';
}

void Seat::updateState(void) {
    this->_State = this->_NextState;
    std::cout << "This is just for testing" << std::endl;
}

#endif // DAY11_H