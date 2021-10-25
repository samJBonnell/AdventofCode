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

int findSum(vector<int>& inputVector);
void fileInput(vector<int>& inputVector, ifstream& in);


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
	cout << findSum(inputVector) << endl;

}

void fileInput(vector<int>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	string IO;
	while (getline(in, IO)) {
		inputVector.push_back(stoi(IO));
	}
}

int findSum(vector<int>& inputVector) {
	for (auto const &ptr : inputVector) {
		for (auto const &ptr2 : inputVector) {
			for (auto const &ptr3 : inputVector)
				if (ptr + ptr2 + ptr3 == 2020) {
					return ptr * ptr2 * ptr3;
				}
		}
	}
}
