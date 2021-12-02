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

class intCodeInstance {
public:
	vector<int> memory;
	vector<int> input;
	vector<int> output;
	int pos;
	bool runCondition;
};

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in);
vector<int> returnMode(int mode);
vector<int> memory_allocate(vector<int>& inputVector);
int returnValue(vector<int> mode, int i);
void computer(intCodeInstance& instance);
void runAmplifier(vector<int>& inputVector);

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

vector<int> returnMode(int mode) {
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
	int permutations[] = { 0, 1, 2, 3, 4 }, i, maxThrust;
	while (next_permutation(permutations, permutations + 5)) {
		i = 0;
		maxThrust = 0;
		for (const auto& ptr : permutations) {
			instanceQueue[i].input.clear();
			instanceQueue[i].output.clear();
			instanceQueue[i].input.push_back(ptr);
			instanceQueue[i++].memory = memory_allocate(inputVector);
		}

		for (int i = 0; i < 5; i++) {
			instanceQueue[i].input.push_back(maxThrust);
			computer(instanceQueue[i]);
			maxThrust = instanceQueue[i].output[0];
			// if (i < 4) instanceQueue[i + 1].input[1] = maxThrust;
		}
		cout << maxThrust << endl;
		maxRef.push_back(maxThrust);
	}
	for (const auto& ptr : maxRef) {
		maxThrust = (maxThrust < ptr) ? ptr : maxThrust;
	}
	cout << "Max thrust is " << maxThrust << endl;
}

vector<int> memory_allocate(vector<int>& inputVector) { // Copies memory into seperate vector to run on each machine. Allocates 2x the memory provided.
	vector<int> copy(inputVector.begin(), inputVector.end());
	copy.resize(copy.size() * 2);
	
	return copy;
}

int returnValue(vector<int> mode, int i) {
	if (mode[i] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void computer(intCodeInstance& instance) {
	vector<int> modeRef;
	instance.pos = 0;
	int a, b, c, inputNum = 0, intPos;
	while (instance.memory[instance.pos] != 99) {
		modeRef = returnMode(instance.memory[instance.pos]);
		for (const auto& ptr : modeRef) {
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
}

/*#include <iostream>
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

void fileInput(vector<INPUT_TYPE>& inputVector, ifstream& in);
vector<int> returnMode(int mode);
vector<int> memory_allocate(vector<int>& inputVector);
int returnValue(vector<int> mode, int i);
int computer(vector<int> memory, vector<int> input);
void runAmplifier(vector<int>& inputVector);

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

vector<int> returnMode(int mode) {
	vector<int> modeStorage;
	for (int i = mode, n = 0; n < 5; n++) {
		modeStorage.push_back(mode % 10);
		mode /= 10;
	}
	return modeStorage;
}

void runAmplifier(vector<int>& inputVector) {
	vector<vector<int>> input(5, vector<int>(2));
	vector<int> maxRef;
	int permutations[] = { 0, 1, 2, 3, 4 }, i, maxThrust = 0;
	while (next_permutation(permutations, permutations + 5)) {
		i = 0;
		input[i][1] = maxThrust = 0;
		for (const auto& ptr : permutations) {
			input[i++][0] = ptr;
		}

		for (int i = 0; i < 5; i++) {
			maxThrust = computer(memory_allocate(inputVector), input[i]);

			if (i < 4) input[i + 1][1] = maxThrust;
		}
		cout << maxThrust << endl;
		maxRef.push_back(maxThrust);
	}
	for (const auto& ptr : maxRef) {
		maxThrust = (maxThrust < ptr) ? ptr : maxThrust;
	}
	cout << "Max thrust is " << maxThrust << endl;
}

vector<int> memory_allocate(vector<int>& inputVector) { // Copies memory into seperate vector to run on each machine. Allocates 2x the memory provided.
	vector<int> copy(inputVector.begin(), inputVector.end());

	copy.resize(copy.size() * 2);

	return copy;
}

int returnValue(vector<int> mode, int i) {
	if (mode[i] == 1) {
		return 1;
	}
	else {
		return 0;
	}
}

int computer(vector<int> memory, vector<int> input) {
	vector<int> modeRef, output;
	int iterator, pos = 0, a, b, c, inputNum = 0, intPos;
	bool useIterator = 1;
	while (memory[pos] != 99) {
		useIterator = 1;
		modeRef = returnMode(memory[pos]);
		switch (modeRef[0]) {
		case 1: // ADD
			a = (returnValue(modeRef, 2)) == 1 ? memory[pos + 1] : memory[memory[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? memory[pos + 2] : memory[memory[pos + 2]];
			c = memory[pos + 3];
			memory[c] = a + b;
			iterator = 4;
			break;
		case 2: // MULTIPLY
			a = (returnValue(modeRef, 2)) == 1 ? memory[pos + 1] : memory[memory[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? memory[pos + 2] : memory[memory[pos + 2]];
			c = memory[pos + 3];
			memory[c] = a * b;
			iterator = 4;
			break;
		case 3: // INPUT
			memory[memory[pos + 1]] = input[inputNum++];
			iterator = 2;
			break;
		case 4: // OUTPUT
			output.push_back(memory[memory[pos + 1]]);
			iterator = 2;
			break;
		case 5: // JUMP IF TRUE
			intPos = (returnValue(modeRef, 2)) == 1 ? memory[pos + 1] : memory[memory[pos + 1]];
			if (intPos != 0) {
				pos = (returnValue(modeRef, 3)) == 1 ? memory[pos + 2] : memory[memory[pos + 2]];
				useIterator = 0;
			}
			else {
				iterator = 3;
			}
			break;
		case 6: // JUMP IF FALSE
			intPos = (returnValue(modeRef, 2)) == 1 ? memory[pos + 1] : memory[memory[pos + 1]];
			if (intPos == 0) {
				pos = (returnValue(modeRef, 3)) == 1 ? memory[pos + 2] : memory[memory[pos + 2]];
				useIterator = 0;
			}
			else {
				iterator = 3;
			}
			break;
		case 7: // LESS THAN
			a = (returnValue(modeRef, 2)) == 1 ? memory[pos + 1] : memory[memory[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? memory[pos + 2] : memory[memory[pos + 2]];
			c = memory[pos + 3];
			(a < b) ? memory[c] = 1 : memory[c] = 0;
			iterator = 4;
			break;
		case 8: // EQUALS
			a = (returnValue(modeRef, 2)) == 1 ? memory[pos + 1] : memory[memory[pos + 1]];
			b = (returnValue(modeRef, 3)) == 1 ? memory[pos + 2] : memory[memory[pos + 2]];
			c = memory[pos + 3];
			(a == b) ? memory[c] = 1 : memory[c] = 0;
			iterator = 4;
			break;
		default:
			cout << "\nError in OPCODE - " << modeRef[0];
			exit(EXIT_FAILURE);
		}
		if (useIterator) pos += iterator;
	}

	return output[0];
}*/
