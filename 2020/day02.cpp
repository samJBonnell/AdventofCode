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

#define RUN_MODE 1

using namespace std;

struct passStruct {
	int upperBound;
	int lowerBound;
	string searchChar;
	string passwordString;
};

void fileInput(vector<passStruct>& inputVector, ifstream& in);
passStruct returnStruct(string IO);
int charCheck(passStruct password);

int main(void) {
	ifstream in;
	string fileName;
	vector<passStruct> inputVector;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}

	int valid = 0;

	fileInput(inputVector, in);
	for (auto const& ptr : inputVector) {
		valid = valid + charCheck(ptr);
	}

	cout << valid << endl;

}

void fileInput(vector<passStruct>& inputVector, ifstream& in) {
	string IO;
	while (getline(in, IO)) {
		inputVector.push_back(returnStruct(IO));
	}
}

passStruct returnStruct(string IO) {
	passStruct password;
	password.lowerBound = stoi(IO.substr(0, IO.find("-")));
	IO.erase(0, IO.find("-") + 1);
	password.upperBound = stoi(IO.substr(0, IO.find(" ")));
	IO.erase(0, IO.find(" ") + 1);
	password.searchChar = IO.substr(0, IO.find(":"));
	IO.erase(0, IO.find(":") + 2);
	password.passwordString = IO;

	return password;
}

int charCheck(passStruct password) {
	if (RUN_MODE == 0) {
		int count = 0;
		for (auto const& ptr : password.passwordString) {
			if (ptr == password.searchChar[0]) count++;
		}
		if (count >= password.lowerBound && count <= password.upperBound) return 1;

		return 0;
	}
	else {
		char first = password.passwordString[password.lowerBound - 1];
		char second = password.passwordString[password.upperBound - 1];

		if (first != second)
			if (first == password.searchChar[0] || second == password.searchChar[0]) return 1;
		
		return 0;
	}
}
