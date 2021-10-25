#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

void _executeCommand(std::string _toExecute, std::vector<std::string>::iterator& _executionIterator, int& accumulator);

int main(void) {
	int accumulator = 0;

	std::vector<std::string> program;
	std::set<int> _usedCommands;
	std::string _inputString;

	while (std::getline(std::cin, _inputString)) {
		program.push_back(_inputString);
	}

	for (auto beg = program.begin(), end = program.end(); beg != end;) {
		if (_usedCommands.find(std::distance(program.begin(), beg)) != _usedCommands.end()) break;
		_usedCommands.insert(std::distance(program.begin(), beg));
		_executeCommand(*beg, beg, accumulator);
	}

	std::cout << "Accumulator = " << accumulator << std::endl;

	return 0;
}

void _executeCommand(std::string _toExecute, std::vector<std::string>::iterator& _executionIterator, int& accumulator) {
	std::string _instruction;
	std::string _modifier;
	std::istringstream _command(_toExecute);
	_command >> _instruction;
	_command >> _modifier;

	if (_instruction == "acc") {
		accumulator += std::stoi(_modifier);
		_executionIterator++;
	}
	else if (_instruction == "jmp") {
		_executionIterator += std::stoi(_modifier);
	}
	else if (_instruction == "nop") {
		_executionIterator++;
	}
}
