#ifndef INSTRUCTIONH
#define INSTRUCTIONH

#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#include <string>
#include <sstream>

class _instruction {
	void friend _changeInstruction(_instruction& instruction);
public:
	_instruction() = default;
	_instruction(std::string& _stringInstruction);

	int64_t returnID() const;
	int64_t returnMOD() const;
	void setID(int64_t);
	void setMOD(int64_t);

private:
	int64_t _instructionIdentifier;
	int64_t _modifier;
};

_instruction::_instruction(std::string& _stringInstruction) {
	std::istringstream _parsingString(_stringInstruction);
	std::string _stringinstructionIdentifier, _stringmodifier;

	_parsingString >> _stringinstructionIdentifier;
	_parsingString >> _stringmodifier;

	if (!_stringinstructionIdentifier.compare("acc")) _instructionIdentifier = 0;
	else if (!_stringinstructionIdentifier.compare("jmp")) _instructionIdentifier = 1;
	else if (!_stringinstructionIdentifier.compare("nop")) _instructionIdentifier = 2;
	else {
		_instructionIdentifier = -1;
		std::cout << "Instruction identifier misset." << std::endl;
	}

	_modifier = std::stoi(_stringmodifier);
}

int64_t _instruction::returnID() const {
	return _instructionIdentifier;
}

int64_t _instruction::returnMOD() const {
	return _modifier;
}

void _instruction::setID(int64_t newID) {
	_instructionIdentifier = newID;
}

void _instruction::setMOD(int64_t newMOD) {
	_modifier = newMOD;
}

void _changeInstruction(_instruction& instruction) {
	if (instruction.returnID() == 1) instruction.setID(2); // If instruction is jmp, change to nop
	else if (instruction.returnID() == 2) instruction.setID(1); // If instruction is nop, change to jmp
}

#endif
