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
#include <map>
#include <iterator>
#include <chrono>

#define INPUT_TYPE string
#define BREAK_CHAR '\n'

using namespace std;
using namespace std::chrono;

class Orbit {
public:
	tuple<string, string> ref;
};

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in);
map<string, string> makeTree(vector<Orbit>& orbits);
Orbit makeOrbit(string parent, string child);
vector<Orbit> makeList(vector<INPUT_TYPE>& inputVector);
int countChildren(map<string, string>& orbits, string child);
void totalOrbits(map<string, string>& orbit);

int main(void) {
	ifstream in;
	string fileName;
	vector<INPUT_TYPE> inputVector;
	vector<Orbit> orbits;
	map<string, string> orbitRef;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(EXIT_FAILURE);
	}
	auto start = high_resolution_clock::now();
	fileInput(inputVector, in);
	orbits = makeList(inputVector);
	orbitRef = makeTree(orbits);
	totalOrbits(orbitRef);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << endl << "Ran for " << duration.count() << " microsecondss" <<endl;
}

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	INPUT_TYPE IO;
	while (getline(in, IO, BREAK_CHAR)) {
		inputVector.push_back(IO);
	}
}

Orbit makeOrbit(string parent, string child) {
	Orbit temp;
	temp.ref = make_tuple(parent, child);
	return temp;
}

vector<Orbit> makeList(vector<INPUT_TYPE>& inputVector) {
	int i = 0, braceSearch;
	vector<Orbit> orbits;

	for (const auto& ptr : inputVector) {
		braceSearch = inputVector[i].find(')');
		orbits.push_back(makeOrbit(inputVector[i].substr(0, braceSearch), inputVector[i].substr(braceSearch + 1)));
		i++;
	}

	return orbits;
}

// Make a map of objects with a pointer to the parent. Traverse through that map. Break the input on the ')' char
map<string, string> makeTree(vector<Orbit>& orbits) {
	map<string, string> parents;
	for (const auto& ptr : orbits) {
		parents.insert({get<1>(ptr.ref), get<0>(ptr.ref)});
		//cout << get<0>(ptr.ref) << get<1>(ptr.ref) << endl;
	}

	/*for (const auto& ptr : parents) {
		cout << ptr.second << ptr.first << endl;
	}*/
	return parents;
}

int countChildren(map<string, string>& orbits, string child) {
	int count = 0;
	while (child != "COM") {
		count++;
		child = orbits.at(child);
	}

	return count;
}

void totalOrbits(map<string, string>& orbit) {
	int count = 0;
	for (const auto& ptr : orbit) {
		count += countChildren(orbit, ptr.first);
	}

	cout << count;
}
