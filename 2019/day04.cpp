#include <iostream>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <regex>
#include <vector>
#include <utility>
#include <cstring>
#include <istream>
#include <string>
#include <sstream>
#include <tuple>
#include <map>
#include <iterator>

using namespace std;

vector<int> digits(int input); 
bool parrellelNums(vector<int> input);
bool adjacentValues(vector<int> input);
bool doubleValues(vector<int> input);

int main(void) {
	int high = 678275, low = 130254, numberofCodes = 0;
	vector<int> intNum;
	for (int i = low; i < high; i++) {
		intNum = digits(i);
		if (parrellelNums(intNum)) {
			if (adjacentValues(intNum)) {
				if (doubleValues(intNum)) {
					numberofCodes++;
				}
			}
		}
		else {
			continue;
		}
	}
	cout << "Number of codes = " << numberofCodes;
}

vector<int> digits(int input) {
	vector<int> digits;
	int num_of_digits = 6;
	for (int i = 0; i < num_of_digits; i++) {
		digits.push_back(input % 10);
		input /= 10;
	}
	return digits;
}

bool parrellelNums(vector<int> input) {
	bool parrellel = 1;
	for (int i = input.size() - 1; i > 0; i--) {
		if (input[i] > input[i - 1]) {
			parrellel = 0;
		}
	}
	return parrellel;
}

bool adjacentValues(vector<int> input) {
	bool adjacent = 0;
	for (int i = input.size() - 1; i > 0; i--) {
		if (input[i] == input[i - 1]) {
			adjacent = 1;
		}
	}
	return adjacent;
}

bool doubleValues(vector<int> input) {
	bool doubleValue = 0;
	vector<int> occuranceValues = {0};
	int referenceforgroups = 1;
	for (int i = input.size() - 1; i > 0; i--) {
		if (input[i] != input[i - 1]) {
			occuranceValues.push_back(referenceforgroups);
			referenceforgroups = 1;
		}
		if (input[i] == input[i - 1]) referenceforgroups++;
	}
	occuranceValues.push_back(referenceforgroups);
	for (int i = 0; i < occuranceValues.size(); i++) {
		if (occuranceValues[i] == 2) doubleValue = 1;
	}

	return doubleValue;
}