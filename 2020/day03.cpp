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

#define widthParam 15
#define inputParam string

using namespace std;

void fileInput(vector<inputParam>& inputVector, ifstream& in);
int countTrees(vector<inputParam>& slopeField, int xSlope, int ySlope);


int main(void) {
	ifstream in;
	string fileName;
	vector<inputParam> slopeField;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}

	vector<pair<int, int>> slopes{ {1,1},{3,1},{5,1 },{7,1},{1, 2} };
	fileInput(slopeField, in);

	long long int treeSum = 1;

	for (auto const& ptr : slopes) {
		treeSum *= countTrees(slopeField, ptr.first, ptr.second);
	}

	cout << treeSum << endl;

}

void fileInput(vector<inputParam>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	string IO;
	while (getline(in, IO)) {
		for (int i = 0; i < widthParam; i++) IO += IO;
		inputVector.push_back(IO);
	}
}

int countTrees(vector<inputParam>& slopeField, int xSlope, int ySlope) {
	int trees = 0;
	int yAxis = 0, xAxis = 0;

	while (yAxis < slopeField.size()) {
		if (slopeField[yAxis][xAxis] == '#') trees++;
		yAxis += ySlope;
		xAxis += xSlope;
	}

	return trees;
}
