#ifndef VIRTUALMACHINEH
#define VIRTUALMACHINEH

#include "day08_instruction.h"

class _virtualMachine {
public:
	_virtualMachine() = default;
	_virtualMachine(const std::vector<_instruction>& _iniInstructions) : _instructionList(_iniInstructions), _instructionIterator(_instructionList.begin()) {};

	void _runVM();
	void _executeInstruction();
	void _checkInstruction();
	void _addInstruction();

	int64_t _returnAcc() const;
	int64_t _returnState() const;

private:
	std::vector<_instruction> _instructionList;
	std::vector<_instruction>::iterator _instructionIterator;
	std::set<int> _usedInstructions;

	int64_t accumulator = 0;
	int64_t _errorState = 0;

};

void _virtualMachine::_runVM() {
	while (_errorState != -1 && _instructionIterator != _instructionList.end()) {
		this->_checkInstruction();		// Checks if an instruction has been previously run. If so, the program will loop infinitely. Sets _errorState to -1.
		if (_errorState == -1) break;	// Checks if an error state has been set. If so, flag and exit the execution of the program.
		this->_addInstruction();
		this->_executeInstruction();
	}

	if (_instructionIterator == _instructionList.end()) std::cout << "Execution completed" << std::endl;
}

void _virtualMachine::_executeInstruction() {
	switch (_instructionIterator->returnID()) {
	case 0: // acc
		accumulator += _instructionIterator->returnMOD();
		_instructionIterator++;
		break;
	case 1: // jmp
		_instructionIterator += _instructionIterator->returnMOD();
		break;
	case 2: // nop
		_instructionIterator++;
		break;
	default:
		std::cout << "Error loading instruction." << std::endl;
		_errorState = -1;
		break;
	}
}

void _virtualMachine::_checkInstruction() {
	if (_usedInstructions.find(std::distance(_instructionList.begin(), _instructionIterator)) != _usedInstructions.end()) _errorState = -1;
}

void _virtualMachine::_addInstruction() {
	_usedInstructions.insert(std::distance(_instructionList.begin(), _instructionIterator));
}

int64_t _virtualMachine::_returnAcc() const {
	return accumulator;
}

int64_t _virtualMachine::_returnState() const {
	return _errorState;
}

#endif
