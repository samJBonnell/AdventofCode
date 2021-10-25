#include <iostream>
#include <iterator>
#include <istream>
#include <vector>
#include <set>
#include <fstream>
#include <algorithm>

constexpr uint8_t PREAMBLE = 25;

typedef std::istream_iterator<uint64_t> i_u64;
typedef std::vector<uint64_t>::iterator vi_u64;
typedef std::vector<uint64_t> v_u64;

// Function prototypes

void sum_in_range2(vi_u64 first, vi_u64 last, const uint64_t& target, bool& error_bit); // sum_in_range takes two vector iterators and identifies if target is a sum of any two values within the "window" range.
void sum_in_rangeN(vi_u64 first, vi_u64 last, const uint64_t& target, bool& error_bit); // sum_in_range takes two iterators and identifies if target is a sum of any number of values in a window range.
void find_XMAS_error(v_u64& XMAS_code, const uint64_t& target); // find_XMAS_error takes two iterators and a target value and returns two iterators that point to the first and last values of the contigous range that sum to the target

int main(void) {
	v_u64 XMAS_code;
	std::ifstream in("input.txt");
	std::copy(i_u64(in), i_u64(), std::inserter(XMAS_code, XMAS_code.end()));

	auto first = XMAS_code.begin(), second = XMAS_code.begin() + PREAMBLE, last = XMAS_code.end();
	auto target = second + 1;
	bool error_bit = false;

	while(second != last && !error_bit) { sum_in_range2(first++, second++, *(target++), error_bit); } 
	if (error_bit) std::cout << std::endl << *(--target) << std::endl;
	find_XMAS_error(XMAS_code, *target);

    return 0;
}

void sum_in_range2(vi_u64 first, vi_u64 last, const uint64_t& target, bool& error_bit) {
    if (first == last) return;

	std::multiset<uint64_t> sums;
    
	for (uint32_t i = 0; first + i - 1 != last; i++) {
		for (uint32_t n = 0; first + n - 1 != last; n++) {
			if (*(first + i) != *(first + n)) sums.insert(*(first + i) + *(first + n));
		}
	}

	error_bit = (sums.find(target) == sums.end());

	return;
}

void sum_in_rangeN(vi_u64 first, vi_u64 last, const uint64_t& target, bool& error_bit) {
	uint64_t sum;
	vi_u64 traversing_iterator;
	std::multiset<uint64_t> setValues;

	for (; first != last && !error_bit; first++) {
		traversing_iterator = first;
		sum = 0;
		while (sum < target && traversing_iterator != last) {
			sum += *(traversing_iterator);
			setValues.insert(*(traversing_iterator++));
		}
		if (sum == target) {
			std::cout << *(std::max_element(setValues.begin(), setValues.end())) + *(std::min_element(setValues.begin(), setValues.end())) << std::endl;
			error_bit = true;
		}
		setValues.clear();
	}

	return;
}

void find_XMAS_error(v_u64& XMAS_code, const uint64_t& target) {
	uint64_t sum = 0;
	v_u64 sub_range_indices;
	bool error_bit = false;

	for (vi_u64 it = XMAS_code.begin(), end = XMAS_code.end(); it != end; it++) { // Find the index of every number that is larger or equal to the target value. These cannot be used for the sum and will be excluded from the next section.
		if (*(it) >= target) sub_range_indices.push_back(std::distance(XMAS_code.begin(), it));
	}

	sub_range_indices.insert(sub_range_indices.begin(), 0); // Insert the first index of the list to ensure there is a starting bound to the first range passed by the iterators.

	for (auto it = sub_range_indices.begin() + 1, end = sub_range_indices.end(); it != end && !error_bit; it++) {
		sum_in_rangeN(XMAS_code.begin() + *(it - 1), XMAS_code.begin() + *it, target, error_bit);
	}

	return;
}