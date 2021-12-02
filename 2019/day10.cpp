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
#include <algorithm>
#include <set>

using namespace std;

#define INPUT_TYPE string
#define BREAK_CHAR '\n'

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in);
vector<tuple<double, double>> asteriodLocations(vector<string>& inputVector);
double findAsteriod(vector<tuple<double, double>>& locations);
int gcd(int a, int b);

int main(void) {
	ifstream in;
	string fileName;
	vector<INPUT_TYPE> inputVector;
	vector<tuple<double, double>> locations;

	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(EXIT_FAILURE);
	}



	fileInput(inputVector, in);
	locations = asteriodLocations(inputVector);
	cout << endl;
	for (const auto& ptr : inputVector) {
		cout << ptr << endl;
	}
	cout << endl;
	/*for (const auto& ptr : locations) {
		cout << "x = " << get<0>(ptr) << "   y = " << get<1>(ptr) << endl;
	}
	cout << endl;*/

	double maxObserved = findAsteriod(locations);
	cout << "Best location observes " << maxObserved << " asteriods" << endl;
	return 0;
}

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in) { // Inputs lines from input doubleo string vector
	string IO;
	while (getline(in, IO, BREAK_CHAR)) {
		inputVector.push_back(IO);
	}
}

vector<tuple<double, double>> asteriodLocations(vector<string>& inputVector) {
	vector<tuple<double, double>> locations;
	int y = 0;
	for (const auto& ptr : inputVector) {
		for (double x = 0; x < ptr.size(); x++) {
			if (ptr[x] == '#') locations.push_back(make_tuple(x, y));
		}
		y++;
	}
	
	return locations;
}

double findAsteriod(vector<tuple<double, double>>& locations) {
	double x1, y1, x2, y2, dx, dy;
	int maxObserved = 0, GCD;
	vector<double> slopeSize;
	set<tuple<double, double>> slopeSet;
	for (const auto& ptr : locations) {
		slopeSet.clear();
		x1 = get<0>(ptr);
		y1 = get<1>(ptr);
		//cout << get<0>(ptr) << " " << get<1>(ptr) << endl << endl;
		for (const auto& ptr2 : locations) {
			x2 = get<0>(ptr2);
			y2 = get<1>(ptr2);
			dx = x2 - x1;
			dy = y2 - y1;
			GCD = gcd(abs(dx), abs(dy));
			if (dx == 0 && dy == 0) {
				continue;
			}
			else {
				slopeSet.insert(make_tuple(dx / GCD, dy/ GCD));
			}
			//cout << get<0>(ptr2)/GCD << " " << get<1>(ptr2)/GCD << " " << ((dx != 0) ? dy / dx : 0) << endl;
		}
		slopeSize.push_back(slopeSet.size());
		//cout << endl;
	}
	for (const auto& ptr : slopeSize) {
		if (maxObserved == 0) maxObserved = ptr;
		maxObserved = (ptr >= maxObserved) ? ptr : maxObserved;
	}

	return maxObserved;
}

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
