#ifndef DAY05_NEW_H
#define DAY05_NEW_H

#include <string>

class Seat {
public:
	// Constructors
	Seat() = default;
	Seat(const std::string& s);

	// Data Operations
	Seat& set(const std::string& s);
	inline Seat& clear ();

	// Return Functions
	inline unsigned long ret_seatID() const { return _seatID; };
	inline unsigned long ret_row() const { return _row; };
	inline unsigned long ret_col() const { return _col; };

private:
	unsigned long _seatID = 0;
	unsigned long _seatBin = 0;
	unsigned long _row = 0;
	unsigned long _col = 0;
};

Seat::Seat(const std::string& s) {
	for (std::string::size_type i = 0; i < s.size(); i++) {
		if (s[i] == 'B' || s[i] == 'R') _seatBin |= 1UL << ((s.size() - 1) - i);
	}

	_row = (_seatBin >> 3);
	_col = (_seatBin & 7);
	_seatID = (_row * 8) + _col;
}

Seat& Seat::set(const std::string& s) {
	this->clear();

	for (std::string::size_type i = 0; i < s.size(); i++) {
		if (s[i] == 'B' || s[i] == 'R') _seatBin |= 1UL << ((s.size() - 1) - i);
	}

	_row = (_seatBin >> 3);
	_col = (_seatBin & 7);
	_seatID = (_row * 8) + _col;

	return *this;
}

inline Seat& Seat::clear(){
	_seatBin = 0;
	_row = 0;
	_col = 0;

	return *this;
}

#endif //DAY05_NEW_H