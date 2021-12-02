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

using namespace std;

void fileInput(vector<float>& inputVector, ifstream& in);
int returnValueofFuel(vector<float>& inputVector);
int returnSum(float value);

int main(void) {
	ifstream in;
	string fileName;
	vector<float> inputVector;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}
	cout << returnSum(100756) << "\n";
	int sum = returnValueofFuel(inputVector);
	cout << "Mass required is " << sum << "\n";

}

void fileInput(vector<float>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	string IO;
	while (getline(in, IO)) {
		inputVector.push_back(stoi(IO));
	}
}

int returnValueofFuel(vector<float>& inputVector) {
	int sum = 0;
	for (int i = 0; i < inputVector.size(); i++) {
		sum += returnSum(inputVector[i]);
	}
	return sum;
}

int returnSum(float value) {
	int sum = floor(value / 3) - 2;
	if (sum > 0) {
		sum += returnSum(sum);
	}
	else {
		sum = 0;
	}
	return sum;
}
