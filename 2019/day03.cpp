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
#include <cstddef>

using namespace std;

void fileInput(vector<string>& lineOne, vector<string>& lineTwo, ifstream& in);
map<tuple<int, int>, int> findTuples(vector<string>& lineOne, vector<tuple<int, int>>& intersectionPoints);
vector<tuple<int, int>> findIntersectionPoints(vector<tuple<int, int>>& lineOne, vector<tuple<int, int>>& lineTwo);
void findshortedDistance(map<tuple<int, int>, int>& referenceMapOne, map<tuple<int, int>, int>& referenceMapTwo, vector<tuple<int, int>>& intersectionPoints);

int main(void) {
	ifstream in;
	string fileName;
	vector<string> lineOne, lineTwo;
	vector<tuple<int, int>> intersectionPointsOne;
	vector<tuple<int, int>> intersectionPointsTwo;
	vector<tuple<int, int>> returnedPoints;
	map<tuple<int, int>, int> referenceMapOne;
	map<tuple<int, int>, int> referenceMapTwo;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(0);
	}
	fileInput(lineOne, lineTwo, in);
	referenceMapOne = findTuples(lineOne, intersectionPointsOne);
	referenceMapTwo = findTuples(lineTwo, intersectionPointsTwo);
	returnedPoints = findIntersectionPoints(intersectionPointsOne, intersectionPointsTwo);
	findshortedDistance(referenceMapOne, referenceMapTwo, returnedPoints);
}

void fileInput(vector<string>& lineOne, vector<string>&lineTwo, ifstream& in) { // Inputs lines from input stringo string vector
	string IO;
	vector<string> intermediateStorage;
	while (getline(in, IO, '\n')) {
		intermediateStorage.push_back(IO);
	}
	stringstream one(intermediateStorage[0]);
	stringstream two(intermediateStorage[1]);
	while (getline(one, IO, ',')) {
		lineOne.push_back(IO);
	}
	while (getline(two, IO, ',')) {
		lineTwo.push_back(IO);
	}
}

map<tuple<int, int>, int> findTuples(vector<string>& line, vector<tuple<int, int>>& intersectionPoints) {
	int x = 0, y = 0, num_of_steps = 0;
	map<tuple<int, int>, int> pointReference;
	tuple<int, int> positionsVisited = { 0, 0 };
	int displacement;
	char direction;
	for (int i = 0; i < line.size(); i++) {
		direction = line[i][0];
		displacement = stoi(line[i].substr(1));
		for (int c = 0; c < displacement; c++) {
			num_of_steps += 1;
			if (direction == 'U') {
				y += 1;
			}
			else if (direction == 'D') {
				y -= 1;
			}
			else if (direction == 'L') {
				x -= 1;
			}
			else if (direction == 'R') {
				x += 1;
			}
			else {
				cout << "Error - Wrong Direction Input\n";
				exit(0);
			}
			get<0>(positionsVisited) = x;
			get<1>(positionsVisited) = y;
			intersectionPoints.push_back(positionsVisited);
			auto search = pointReference.find(positionsVisited);
			if (search != pointReference.end()) {
				continue;
			}
			else { // Not Found in Map
				pointReference.insert({ positionsVisited, num_of_steps });
			}
		}
	/*for (int i = 0; i < intersectionPoints.size(); i++) {
		cout << get<0>(intersectionPoints[i]) << " " << get<1>(intersectionPoints[i]) << "\n";
		}*/
	}
	return pointReference;
}

vector<tuple<int,int>> findIntersectionPoints(vector<tuple<int, int>>& lineOne, vector<tuple<int, int>>& lineTwo) {
	int manhattenDistance, test;
	vector<tuple<int, int>> foundIntersection;
	bool a = 1;
	for (int i = 0; i < lineOne.size(); i++) {
		for (int n = 0; n < lineTwo.size(); n++) {
			if (lineOne[i] == lineTwo[n]) {
				foundIntersection.push_back(lineOne[i]);
				if (a) {
					manhattenDistance = abs(get<0>(lineOne[i])) + abs(get<1>(lineOne[i]));
					a = 0;
				}
				test = abs(get<0>(lineOne[i])) + abs(get<1>(lineOne[i]));
				if (test <= manhattenDistance) {
					manhattenDistance = test;
				}
			}
			else {
				continue;
			}
		}
	}
	if (!manhattenDistance) {
		cout << "Manhatten Distance is " << manhattenDistance << "\n";
	}
	else {
		cout << "Could not initialize int(manhattenDistance) - Exiting\n";
		exit(0);
	}
	return foundIntersection;
}

void findshortedDistance(map<tuple<int, int>, int>& referenceMapOne, map<tuple<int,int>, int>& referenceMapTwo,vector<tuple<int,int>> &intersectionPoints) {
	int shortestDistance, intOne, intTwo;
	bool a = 1;
	for (int i = 0; i < intersectionPoints.size(); i++) {
		auto search = referenceMapOne.find(intersectionPoints[i]);
		if (search != referenceMapOne.end()) {
			intOne = referenceMapOne.at(intersectionPoints[i]);
		}
		search = referenceMapTwo.find(intersectionPoints[i]);
		if (search != referenceMapTwo.end()) {
			intTwo = referenceMapTwo.at(intersectionPoints[i]);
		}
		if (a) {
			shortestDistance = intOne + intTwo;
			a = 0;
		}
		if (intOne + intTwo <= shortestDistance) {
			shortestDistance = intOne + intTwo;
		}
	}

	cout << "Shortest Distance to Intersection is " << shortestDistance << "\n";
}
