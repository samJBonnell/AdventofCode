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
#include <algorithm>
#include <tuple>;
#include <map>

#define INPUT_TYPE int

using namespace std;

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in);
vector<vector<vector<int>>> breakintoLayers(vector<INPUT_TYPE>& input, int width, int height);
void renderImage(vector<vector<vector<int>>>& layers, int width, int height);

class mapFunctions {
public:
	int getMin(const map<int, int>& mymap);
};

int mapFunctions::getMin(const map<int, int>& mymap) {
	auto it = min_element(begin(mymap), end(mymap), [](const auto& l, const auto& r) { return l.first < r.first; });
	return it->second;
}

int main(void) {
	ifstream in;
	string fileName;
	vector<INPUT_TYPE> inputVector;
	vector<vector<vector<int>>> layers;
	int width, height, numofLayers;
	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(EXIT_FAILURE);
	}
	cout << endl << "Enter width value\n";
	cin >> width;
	cout << endl << "Enter height value\n";
	cin >> height;
	cout << endl;

	fileInput(inputVector, in);
	numofLayers = inputVector.size() / (width * height);
	layers = breakintoLayers(inputVector, width, height); // First value is width, second it height
	renderImage(layers, width, height);
}

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	int i = 0, char_to_int, n = 0;
	string IO;
	vector<string> intVector;
	while (getline(in, IO)) {
		intVector.push_back(IO);
	}
	for (const auto& ptr : intVector[i]) { 
		int char_to_int = (int)ptr - 48;
		inputVector.push_back(char_to_int);
	}
}

vector<vector<vector<int>>> breakintoLayers(vector<INPUT_TYPE>& input, int width, int height) {
	int numofLayers = input.size() / (width * height);
	map<int, int> minZeros;
	int ref = 0, zero = 0, one = 0, two = 0;
	vector<vector<vector<int>>> layers(numofLayers, vector<vector<int> >(height, vector <int>(width)));
	for (int i = 0; i < numofLayers; i++) {
		for (int n = 0; n < height; n++) {
			for (int x = 0; x < width; x++) {
				layers[i][n][x] = input[ref++];
				if (input[ref - 1] == 0) zero++;
				if (input[ref - 1] == 1) one++;
				if (input[ref - 1] == 2) two++;
			}
		}
		minZeros.insert({ zero, one * two });
		zero = one = two = 0;
	}
	
	mapFunctions min;
	// cout << endl << min.getMin(minZeros);
	return layers;
}

void renderImage(vector<vector<vector<int>>>& layers, int width, int height) {
	vector<vector<string>> image(height, vector<string>(width));
	int numofLayers = layers.size();
	for (int i = 0; i < numofLayers; i++) {
		for (int n = 0; n < height; n++) {
			for (int x = 0; x < width; x++) {
				image[n][x] = (layers[i][n][x] == 0 && image[n][x] == "") ? " " : image[n][x];
				image[n][x] = (layers[i][n][x] == 1 && image[n][x] == "") ? "I" : image[n][x];
			}
		}
	}

	for (int i = 0; i < height; i++) {
		for (int n = 0; n < width; n++) {
			cout << image[i][n];
		}
		cout << endl;
	}
}
