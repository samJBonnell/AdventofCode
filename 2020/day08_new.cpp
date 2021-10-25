#include "day08_virtualMachine.h"

int main(void) {
	std::string _inputString;
	std::vector<_instruction> iniProgram;

	int64_t globalAccumulator = 0;

	while (std::getline(std::cin, _inputString)) {
		_instruction tempInstruction(_inputString);
		iniProgram.push_back(tempInstruction);
	}

	std::vector<std::vector<_instruction>> program_trials;

	for (auto& ptr : iniProgram) {
		_instruction iniState = ptr;
		_changeInstruction(ptr);
		program_trials.push_back(iniProgram);
		ptr = iniState;
	}

	for (const auto& program_iter : program_trials) {
		_virtualMachine VM(program_iter);
		VM._runVM();

		if (VM._returnState() != -1) std::cout << VM._returnAcc() << std::endl;
	}

	return 0;
}