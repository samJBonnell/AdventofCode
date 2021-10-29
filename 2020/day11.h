#ifndef DAY11_H
#define DAY11_H

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

class Seat {
public:
    Seat() = default;
    Seat(char iniState) : _State(iniState), _NextState(' ') {};

    void queueUpdate(std::array<Seat, 8>& adjacentSeats);
    bool returnState(void) const { return (_State == '#') ? 1 : 0; }; // If the seat is occupied, return 1, else, return 0;
    void updateState();

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
    this->_NextState = ' ';
}

class SeatingArrangment {
public:
    SeatingArrangment() = default;
    SeatingArrangment(std::istream& in);

    void updateSeatingArrangment();
    std::array<Seat, 8> SeatingArrangment::returnAdjacentSeats(uint8_t& row, uint8_t& col) const;

private:
    std::vector<std::vector<Seat>> Seats;
};

SeatingArrangment::SeatingArrangment(std::istream& in) {
    std::string inputRow;
    std::vector<Seat> rowVector;

    while (std::getline(in, inputRow)) {
        std::stringstream col(inputRow);

        for (const auto& colState : inputRow) rowVector.push_back(Seat(colState));
        Seats.push_back(rowVector);
    }
}

void SeatingArrangment::updateSeatingArrangment() {
    for (auto& row : Seats) for (auto& col : row) col.updateState();
}

std::array<Seat, 8> SeatingArrangment::returnAdjacentSeats(uint8_t& row, uint8_t& col) const {
    std::array<Seat, 8> adjacentSeats;
    int rowFactor, colFactor;

    if (row - 1 < 0) rowFactor;
    if (row + 1 > Seats.size());

    if (col - 1 < 0) ;
    if (col - 1 > Seats[0].size());

    for (auto rowIT = Seats.begin() + rowFactor, endIT = Seats.begin() + 3; rowIT != endIT; rowIT);

}

#endif // DAY11_H