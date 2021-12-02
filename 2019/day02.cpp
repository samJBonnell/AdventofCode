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
int step_in_opcode(vector<int>& input, int x, int y);
void findInputMemory(vector<int>& input);

int main(void) {
	ifstream in;
	string fileName;
	vector<int> inputVector;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}
	fileInput(inputVector, in);
	findInputMemory(inputVector);
}

void fileInput(vector<int>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	string IO;
	while (getline(in, IO, ',')) {
		inputVector.push_back(stoi(IO));
	}
}

void findInputMemory(vector<int>& input) {
	vector<int> copy;
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {
			copy.clear();
			for (int i = 0; i < input.size(); i++) {
				copy.push_back(input[i]);
			}
			if (step_in_opcode(copy, x, y) == 19690720) {
				cout << "Noun and Verb Code = " << (100 * x) + y;
			}
		}
	}
}

int step_in_opcode(vector<int>& input, int x, int y) {
	input[1] = x;
	input[2] = y;
	int pos1 = 0, pos2, pos3, pos4;
	while (input[pos1] != 99) {
		pos2 = input[pos1 + 1];
		pos3 = input[pos1 + 2];
		pos4 = input[pos1 + 3];
		if (input[pos1] == 1) {
			input[pos4] = input[pos2] + input[pos3];
		}
		else if (input[pos1] == 2) {
			input[pos4] = input[pos2] * input[pos3];
		}
		else {
			cout << "Bad OPCODE - Exiting\n";
			exit(0);
		}
		pos1 += 4;
	}
	return input[0];
}
