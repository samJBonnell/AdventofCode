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

using namespace std;

void fileInput(vector<int>& inputVector, ifstream& in);
vector<int> returnMode(int mode);
void computer(vector<int>& input);

int main(void) {
	ifstream in;
	string fileName;
	vector<int> inputVector;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(EXIT_FAILURE);
	}
	fileInput(inputVector, in);
	
	computer(inputVector);
}

void fileInput(vector<int>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	string IO;
	while (getline(in, IO, ',')) {
		inputVector.push_back(stoi(IO));
	}
}

vector<int> returnMode(int mode) {
	vector<int> modeStorage;
	for (int i = mode, n = 0; n < 5; n++) {
		modeStorage.push_back(mode % 10);
		mode /= 10;
	}
	return modeStorage;
}

int returnValue(vector<int> mode, int i) {
	if (mode[i] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void computer(vector<int>& input) {
	vector<int> modeRef, output;
	int iterator, pos = 0, a, b, c, inputNum, intPos;
	bool useIterator = 1;
	while (input[pos] != 99) {
		useIterator = 1;
		modeRef = returnMode(input[pos]);
		switch(modeRef[0]) {
		case 1: // ADD
			a = (returnValue(modeRef, 2)) == 1 ? input[pos + 1] : input[input[pos + 1]]; 
			b = (returnValue(modeRef, 3)) == 1 ? input[pos + 2] : input[input[pos + 2]]; 
			c = input[pos + 3];
			input[c] = a + b;
			iterator = 4;
			break;
		case 2: // MULTIPLY
			a = (returnValue(modeRef, 2)) == 1 ? input[pos + 1] : input[input[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? input[pos + 2] : input[input[pos + 2]];
			c = input[pos + 3];
			input[c] = a * b;
			iterator = 4;
			break;
		case 3: // INPUT
			cout << "Enter value for input\n";
			cin >> inputNum;
			input[input[pos + 1]] = inputNum;
			iterator = 2;
			break;
		case 4: // OUTPUT
			cout << input[input[pos + 1]];
			iterator = 2;
			break;
		case 5: // JUMP IF TRUE
			intPos = (returnValue(modeRef, 2)) == 1 ? input[pos + 1] : input[input[pos + 1]];
			if (intPos != 0) {
				pos = (returnValue(modeRef, 3)) == 1 ? input[pos + 2] : input[input[pos + 2]];
				useIterator = 0;
			}
			else {
				iterator = 3;
			}
			break;
		case 6: // JUMP IF FALSE
			intPos = (returnValue(modeRef, 2)) == 1 ? input[pos + 1] : input[input[pos + 1]];
			if (intPos == 0) {
				pos = (returnValue(modeRef, 3)) == 1 ? input[pos + 2] : input[input[pos + 2]];
				useIterator = 0;
			}
			else {
				iterator = 3;
			}
			break;
		case 7: // LESS THAN
			a = (returnValue(modeRef, 2)) == 1 ? input[pos + 1] : input[input[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? input[pos + 2] : input[input[pos + 2]];
			c = input[pos + 3];
			(a < b) ? input[c] = 1 : input[c] = 0;
			iterator = 4;
			break;
		case 8: // EQUALS
			a = (returnValue(modeRef, 2)) == 1 ? input[pos + 1] : input[input[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? input[pos + 2] : input[input[pos + 2]];
			c = input[pos + 3];
			(a == b) ? input[c] = 1 : input[c] = 0;
			iterator = 4;
			break;
		default:
			cout << "\nError in OPCODE - " << modeRef[0];
			exit(EXIT_FAILURE);
		}
		if (useIterator) pos += iterator;
	}
}
