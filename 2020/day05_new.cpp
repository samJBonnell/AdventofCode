#include <iostream>
#include <vector>
#include <algorithm>
#include "day05_new.h"

int main(void) {
	Seat current_Seat;
	std::vector<unsigned long> seatIDs;
	std::string input;
	unsigned long max_seatID = 0, current_seatID = 0;;

	// Part One

	while (std::cin >> input) {
		seatIDs.push_back(current_Seat.set(input).ret_seatID()); // Initializes part two vector and current_Seat object
		max_seatID = (current_Seat.ret_seatID() > max_seatID) ? current_Seat.ret_seatID() : max_seatID;
	}

	std::cout << max_seatID << std::endl;

	// Part Two

	std::sort(seatIDs.begin(), seatIDs.end());

	for (auto b = seatIDs.cbegin(), e = seatIDs.cend(); b != e; b++) {
		if (*b != *(b + 1) - 1) { std::cout << (*b) + 1 << std::endl; break; }
	}

	return 0;
}
