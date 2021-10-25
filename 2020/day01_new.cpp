#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

constexpr unsigned sum = 2020;

unsigned currencySum(std::vector<int>& inputVector);

int main(void) {
	std::istream_iterator<int> in(std::cin), eof;
	std::vector<int> currency(in, eof);

	std::cout << std::endl << currencySum(currency) << std::endl;
	
	return 0;
}

unsigned currencySum(std::vector<int>& inputVector) {
	auto beg = inputVector.begin(), end = inputVector.end(), temp = beg + 1;
	std::sort(beg, end);
	
	if (beg == end) return 0;
	for (; beg < end - 2; beg++) {
		while (temp < end - 1) {
			if ((*beg) + (*temp) + (*(end - 1)) == sum) {
				return (*beg) * (*temp) * (*(end - 1));
			}
			else if ((*beg) + (*temp) + (*(end - 1)) < sum) ++temp;
			else {
				--end;
			}
		}

		temp = beg + 1;
		end = inputVector.end();
	}

	return 0;
}
