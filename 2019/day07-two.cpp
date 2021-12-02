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

#define INPUT_TYPE int
#define BREAK_CHAR ','

using namespace std;

class intCodeInstance { // Class used to hold all values for a register during the pause phase. Reset for each pass through the permutations.
public:
	vector<int> memory;
	vector<int> input;
	vector<int> output;
	int pos;
	bool runCondition;
	bool endRunTime;
};

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in);
vector<int> returnMode(int mode);
vector<int> memory_allocate(vector<int>& inputVector);
int returnValue(vector<int> mode, int i);
void computer(intCodeInstance& instance);
void runAmplifier(vector<int>& inputVector);
void resetInstance(intCodeInstance& ptr, vector<int>& memory, int permutationRef);

int main(void) {
	ifstream in;
	string fileName;
	vector<INPUT_TYPE> inputVector;

	cout << "Enter File Name\n";
	cin >> fileName;
	in.open(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error - Exiting";
		exit(EXIT_FAILURE);
	}
	
	fileInput(inputVector, in);
	runAmplifier(inputVector);
}

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in) { // Inputs lines from input into string vector
	string IO;
	while (getline(in, IO, BREAK_CHAR)) {
		inputVector.push_back(stoi(IO));
	}
}

vector<int> returnMode(int mode) { // Returns a vector with the bits of the mode arranged in the input order.
	vector<int> modeStorage;
	for (int i = mode, n = 0; n < 5; n++) {
		modeStorage.push_back(mode % 10);
		mode /= 10;
	}
	return modeStorage;
}

void runAmplifier(vector<int>& inputVector) {
	vector<intCodeInstance> instanceQueue(5);
	vector<int> maxRef;
	int permutations[] = { 5, 6, 7, 8, 9 }, i, maxThrust;
	while (next_permutation(permutations, permutations + sizeof(permutations)/sizeof(int))) {
		i = 0;
		maxThrust = 0;
		for (const auto& ptr : permutations) { // Sets all values needed for input into the computer. Sets the intial permutation bit in the first slot of the input vector in the intCodeInstance class.
			resetInstance(instanceQueue[i++], inputVector, ptr);
		}
		while (!instanceQueue[instanceQueue.size() - 1].endRunTime) {
			i = 0;
			for (const auto& ptr : instanceQueue) {
				instanceQueue[i].input.push_back(maxThrust);
				computer(instanceQueue[i]);
				maxThrust = instanceQueue[i].output[instanceQueue[i].output.size() -1];
				instanceQueue[i++].input.clear(); // Removes previous input into the computer to make room for the next entry.
			}
		}
		// cout << maxThrust << endl;
		maxRef.push_back(maxThrust);
	}
	for (const auto& ptr : maxRef) {
		maxThrust = (maxThrust < ptr) ? ptr : maxThrust;
	}
	cout << "Max thrust is " << maxThrust << endl;
}

vector<int> memory_allocate(vector<int>& inputVector) { // Copies memory into seperate vector to run on each machine. Allocates 2x the memory provided.
	vector<int> copy(inputVector.begin(), inputVector.end());
	copy.resize(copy.size() * 1); // Set back to two for day nine
	
	return copy;
}

void resetInstance(intCodeInstance& ptr, vector<int>& memory, int permutationRef) { // Called to reset the values so no carryover is observed between trials of permutations
	ptr.pos = NULL;
	ptr.input.clear();
	ptr.output.clear();
	ptr.input.push_back(permutationRef);
	ptr.memory = memory_allocate(memory);
}

int returnValue(vector<int> mode, int i) { // Checks if computation should be done by reference of value
	if (mode[i] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void computer(intCodeInstance& instance) {
	vector<int> modeRef;
	instance.runCondition = true;
	instance.endRunTime = false;
	if (instance.pos == NULL) {
		instance.pos = 0;
	}
	int a, b, c, inputNum = 0, intPos;
	while (instance.memory[instance.pos] != 99 && instance.runCondition == true) {
		modeRef = returnMode(instance.memory[instance.pos]);
		for (const auto& ptr : instance.memory) {
			cout << ptr << " ";
		}
		cout << endl;
		switch (modeRef[0]) {
		case 1: // ADD
			a = (returnValue(modeRef, 2)) == 1 ? instance.memory[instance.pos + 1] : instance.memory[instance.memory[instance.pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? instance.memory[instance.pos + 2] : instance.memory[instance.memory[instance.pos + 2]];
			c = instance.memory[instance.pos + 3];
			instance.memory[c] = a + b;
			instance.pos += 4;
			break;
		case 2: // MULTIPLY
			a = (returnValue(modeRef, 2)) == 1 ? instance.memory[instance.pos + 1] : instance.memory[instance.memory[instance.pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? instance.memory[instance.pos + 2] : instance.memory[instance.memory[instance.pos + 2]];
			c = instance.memory[instance.pos + 3];
			instance.memory[c] = a * b;
			instance.pos += 4;
			break;
		case 3: // INPUT
			instance.memory[instance.memory[instance.pos + 1]] = instance.input[inputNum++];
			instance.pos += 2;
			break;
		case 4: // OUTPUT
			instance.output.push_back(instance.memory[instance.memory[instance.pos + 1]]);
			instance.pos += 2;
			instance.runCondition = false;
			break;
		case 5: // JUMP IF TRUE
			intPos = (returnValue(modeRef, 2)) == 1 ? instance.memory[instance.pos + 1] : instance.memory[instance.memory[instance.pos + 1]];
			if (intPos != 0) {
				instance.pos = (returnValue(modeRef, 3)) == 1 ? instance.memory[instance.pos + 2] : instance.memory[instance.memory[instance.pos + 2]];
			}
			else {
				instance.pos += 3;
			}
			break;
		case 6: // JUMP IF FALSE
			intPos = (returnValue(modeRef, 2)) == 1 ? instance.memory[instance.pos + 1] : instance.memory[instance.memory[instance.pos + 1]];
			if (intPos == 0) {
				instance.pos = (returnValue(modeRef, 3)) == 1 ? instance.memory[instance.pos + 2] : instance.memory[instance.memory[instance.pos + 2]];
			}
			else {
				instance.pos += 3;
			}
			break;
		case 7: // LESS THAN
			a = (returnValue(modeRef, 2)) == 1 ? instance.memory[instance.pos + 1] : instance.memory[instance.memory[instance.pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? instance.memory[instance.pos + 2] : instance.memory[instance.memory[instance.pos + 2]];
			c = instance.memory[instance.pos + 3];
			(a < b) ? instance.memory[c] = 1 : instance.memory[c] = 0;
			instance.pos += 4;
			break;
		case 8: // EQUALS
			a = (returnValue(modeRef, 2)) == 1 ? instance.memory[instance.pos + 1] : instance.memory[instance.memory[instance.pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? instance.memory[instance.pos + 2] : instance.memory[instance.memory[instance.pos + 2]];
			c = instance.memory[instance.pos + 3];
			(a == b) ? instance.memory[c] = 1 : instance.memory[c] = 0;
			instance.pos += 4;
			break;
		default:
			cout << "\nError in OPCODE - " << modeRef[0];
			exit(EXIT_FAILURE);
		}
	}
	if (instance.memory[instance.pos] == 99) instance.endRunTime = true;
}
