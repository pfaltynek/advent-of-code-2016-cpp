#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

//#define TEST 1

#ifdef TEST
const int part1_val1 = 5;
const int part1_val2 = 2;
const std::string input_filename = "input-test.txt";
#else
const int part1_val1 = 61;
const int part1_val2 = 17;
const std::string input_filename = "input.txt";
#endif

std::regex regex_number("-?\\d+");
std::regex regex_instruction("(cpy|inc|dec|jnz)");
std::regex regex_register("[a-d]");
std::regex regex_operand("[a-d]|-?\\d+");

typedef enum {
	INST_CP,
	INST_LD,
	INST_INC,
	INST_DEC,
	INST_JNZ
} INST_TYPE;

typedef enum {
	REG_NONE,
	REG_A,
	REG_B,
	REG_C,
	REG_D
} REG_TYPE;

typedef struct {
	INST_TYPE inst_type;
	int value;
	REG_TYPE reg1, reg2;
} INSTRUCTION;

bool CheckInstruction(std::string instruction_line, std::string &instruction, std::string &operand1, std::string &operand2) {
	std::regex line_template("(cpy|inc|dec|jnz) ([a-d]|-?\\d+) ?([a-d]|-?\\d+)?");

	std::smatch sm;

	if (regex_search(instruction_line, sm, line_template)) {
		if (regex_search(instruction_line, sm, regex_instruction)) {
			instruction = sm[0].str();
			instruction_line = sm.suffix().str();
			if (regex_search(instruction_line, sm, regex_operand)) {
				operand1 = sm[0].str();
				instruction_line = sm.suffix().str();
				if (regex_search(instruction_line, sm, regex_operand)) {
					operand2 = sm[0].str();
				} else {
					operand2 = "";
				}
				return true;
			}
		}
	}
	return false;
}

bool DecodeRegister(std::string operand, REG_TYPE &reg) {
	reg = REG_TYPE::REG_NONE;

	if (operand.size() == 1) {
		switch (operand[0]) {
			case 'a':
				reg = REG_TYPE::REG_D;
				break;
			case 'b':
				reg = REG_TYPE::REG_D;
				break;
			case 'c':
				reg = REG_TYPE::REG_D;
				break;
			case 'd':
				reg = REG_TYPE::REG_D;
				break;
			default:
				return false;
		}
		return true;
	}
	return false;
}

int main(void) {
	std::ifstream input;
	std::string line, inst, op1, op2;
	int result1, result2, cnt;
	std::vector<INSTRUCTION> prg;

	std::cout << "=== Advent of Code 2016 - day 12 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open(input_filename, std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	cnt = 0;
	prg.clear();

	while (std::getline(input, line)) {
		cnt++;
		INSTRUCTION instruction;
		instruction.value = 0;
		instruction.reg1 = REG_TYPE::REG_NONE;
		instruction.reg2 = REG_TYPE::REG_NONE;

		if (!CheckInstruction(line, inst, op1, op2)) {
			std::cout << "Invalid instruction at line" << cnt << std::endl;
			return -1;
		}
		
		switch (inst[0]) {
			case 'c':

				break;
			case 'i':
				if (!DecodeRegister(op1, instruction.reg1)) {
					std::cout << "Invalid \'inc \'instruction at line" << cnt << std::endl;
					return -1;
				}
				instruction.inst_type = INST_INC;
				break;
			case 'd':
				if (!DecodeRegister(op1, instruction.reg1)) {
					std::cout << "Invalid \'dec \'instruction at line" << cnt << std::endl;
					return -1;
				}
				instruction.inst_type = INST_DEC;
				break;
			case 'j':

				break;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
