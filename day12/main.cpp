#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

//#define TEST 1

#ifdef TEST
const std::string input_filename = "input-test.txt";
#else
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
	INST_JNZ,
	INST_JMP,
	INST_NOP
} INST_TYPE;

#define REG_A_IDX 0
#define REG_B_IDX 1
#define REG_C_IDX 2
#define REG_D_IDX 3

typedef struct {
	INST_TYPE inst_type;
	int value;
	int reg1, reg2;
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

void Trace(std::vector<INSTRUCTION> prg, int c_value, int &result1) {
	int regs[4] = {0, 0, 0, 0};
	int pc = 0;

	regs[REG_C_IDX] = c_value;

	while ((pc >= 0) && (pc < prg.size())) {
		switch (prg[pc].inst_type) {
			case INST_CP:
				regs[prg[pc].reg2] = regs[prg[pc].reg1];
				pc++;
				break;

			case INST_LD:
				regs[prg[pc].reg1] = prg[pc].value;
				pc++;
				break;

			case INST_INC:
				regs[prg[pc].reg1]++;
				pc++;
				break;

			case INST_DEC:
				regs[prg[pc].reg1]--;
				pc++;
				break;

			case INST_JNZ:
				if (regs[prg[pc].reg1]) {
					pc += prg[pc].value;
				} else {
					pc++;
				}
				break;

			case INST_JMP:
				pc += prg[pc].value;
				break;

			case INST_NOP:
				pc++;
				break;
		}
	}

	result1 = regs[REG_A_IDX];
}

bool DecodeRegister(std::string operand, int &reg) {
	reg = REG_A_IDX;

	if (operand.size() == 1) {
		switch (operand[0]) {
			case 'a':
				reg = REG_A_IDX;
				break;
			case 'b':
				reg = REG_B_IDX;
				break;
			case 'c':
				reg = REG_C_IDX;
				break;
			case 'd':
				reg = REG_D_IDX;
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
		instruction.reg1 = REG_A_IDX;
		instruction.reg2 = REG_A_IDX;

		if (!CheckInstruction(line, inst, op1, op2)) {
			std::cout << "Invalid instruction at line " << cnt << std::endl;
			return -1;
		}

		switch (inst[0]) {
			case 'c':
				if (DecodeRegister(op1, instruction.reg1)) {
					instruction.inst_type = INST_CP;
					if (!DecodeRegister(op2, instruction.reg2)) {
						std::cout << "Invalid instruction \'cpy\' at line " << cnt << std::endl;
						return -1;
					}
				} else {
					instruction.inst_type = INST_LD;
					instruction.value = atoi(op1.c_str());
					if (!DecodeRegister(op2, instruction.reg1)) {
						std::cout << "Invalid instruction \'cpy\' at line " << cnt << std::endl;
						return -1;
					}
				}
				break;
			case 'i':
				if (!DecodeRegister(op1, instruction.reg1)) {
					std::cout << "Invalid \'inc \'instruction at line " << cnt << std::endl;
					return -1;
				}
				instruction.inst_type = INST_INC;
				break;
			case 'd':
				if (!DecodeRegister(op1, instruction.reg1)) {
					std::cout << "Invalid \'dec \'instruction at line  " << cnt << std::endl;
					return -1;
				}
				instruction.inst_type = INST_DEC;
				break;
			case 'j':
				if (!DecodeRegister(op1, instruction.reg1)) {
					if (atoi(op1.c_str())) {
						instruction.inst_type = INST_JMP;
						instruction.value = atoi(op2.c_str());
					} else {
						instruction.inst_type = INST_NOP;
					}
				} else {
					instruction.inst_type = INST_JNZ;
					instruction.value = atoi(op2.c_str());
				}
				break;
		}
		prg.push_back(instruction);
	}

	if (input.is_open()) {
		input.close();
	}

	Trace(prg, 0, result1);
	Trace(prg, 1, result2);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
