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
#include <cmath>

#define INPUT_PARAM string

using namespace std;

class binary { // Custom Binary Datatype
public:
	vector<int> binaryBits;

	void appendBits(vector<int>& binaryBits) {
		while (binaryBits.size() % 8 != 0) {
			binaryBits.insert(binaryBits.begin(), 0);
		}
	}

	int returnInt(vector<int>& binaryBits) {
		int binInt = 0;
		int ref = binaryBits.size() - 1;
		for (auto const& ptr : binaryBits) {
			binInt += (pow(2, ref--%8) * ptr);
		}
		
		return binInt;
	}
};

void fileInput(vector<INPUT_PARAM>& inputVector, ifstream& in);
pair<int, int> binaryRow(string input);
int product(vector<pair<int, int>>& binaries);
void returnMissing(vector<pair<int, int>>& binaries);


int main(void) {
	ifstream in;
	string fileName;
	vector<INPUT_PARAM> inputVector;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}

	vector<pair<int, int>> binaries;

	fileInput(inputVector, in);
	for (auto const& ptr : inputVector) {
		binaries.push_back(binaryRow(ptr));
	}
	
	cout << product(binaries) << endl;
	returnMissing(binaries);

	return 0;
}

void fileInput(vector<INPUT_PARAM>& inputVector, ifstream& in) { // File Input
	string IO;
	while (getline(in, IO)) {
		inputVector.push_back(IO);
	}
}

pair<int, int> binaryRow(string input) { // Part One
	pair<int, int> binaryReturn;
	binary binOne, binTwo;

	for (int i = 0; i < 7; i++) {
		if (input[i] == 'F') binOne.binaryBits.push_back(0);
		if (input[i] == 'B') binOne.binaryBits.push_back(1);
	}
	for (int i = 7; i < 10; i++) {
		if (input[i] == 'R') binTwo.binaryBits.push_back(1);
		if (input[i] == 'L') binTwo.binaryBits.push_back(0);
	}


	binOne.appendBits(binOne.binaryBits);
	binTwo.appendBits(binTwo.binaryBits);

	int binOneInt = binOne.returnInt(binOne.binaryBits);
	int binTwoInt = binTwo.returnInt(binTwo.binaryBits);

	binaryReturn.first = binOneInt;
	binaryReturn.second = binTwoInt;

	return binaryReturn;
}

int product(vector<pair<int, int>>& binaries) {
	int maxProduct = 0;
	for (auto const& ptr : binaries) {
		maxProduct = ((ptr.first * 8) + ptr.second >= maxProduct) ? (ptr.first * 8) + ptr.second : maxProduct;
	}

	return maxProduct;
}

void returnMissing(vector<pair<int, int>>& binaries) { // Part Two
	vector<int> IDs;
	for (auto const& ptr : binaries) {
		IDs.push_back((ptr.first * 8) + ptr.second);
	}
	sort(IDs.begin(), IDs.end());

	for (int i = 0; i < IDs.size() - 1; i++) {
		if (IDs[i] != IDs[i + 1]-1) cout << IDs[i] + 1 << endl;
	}

}
