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
	INST_CPY,
	INST_INC,
	INST_DEC,
	INST_JNZ
} INST_TYPE;

#define REG_A_IDX 0
#define REG_B_IDX 1
#define REG_C_IDX 2
#define REG_D_IDX 3

typedef struct {
	INST_TYPE inst_type;
	int op1, op2;
	bool op1_is_register, op2_is_register;
} INSTRUCTION;

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

bool DecodeInstruction(std::string line, INSTRUCTION &inst) {
	std::regex cpy1_template("^cpy ([a-d]) ([a-d])$");
	std::regex cpy2_template("^cpy (-?\\d+) ([a-d])$");
	std::regex inc_template("^inc ([a-d])$");
	std::regex dec_template("^dec ([a-d])$");
	std::regex jnz1_template("^jnz ([a-d]) ([a-d])?$");
	std::regex jnz2_template("^jnz ([a-d]) (-?\\d+)?$");
	std::regex jnz3_template("^jnz (-?\\d+) ([a-d])?$");
	std::regex jnz4_template("^jnz (-?\\d+) (-?\\d+)?$");
	std::smatch sm;

	inst.op1_is_register = true;
	inst.op2_is_register = true;

	if (regex_match(line, sm, cpy1_template)) {
		inst.inst_type = INST_CPY;

		if (DecodeRegister(sm.str(1), inst.op1)) {
			if (DecodeRegister(sm.str(2), inst.op2)) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (regex_match(line, sm, cpy2_template)) {
		inst.inst_type = INST_CPY;
		inst.op1_is_register = false;

		inst.op1 = atoi(sm.str(1).c_str());

		if (DecodeRegister(sm.str(2), inst.op2)) {
			return true;
		} else {
			return false;
		}
	} else if (regex_match(line, sm, inc_template)) {
		inst.inst_type = INST_INC;

		if (DecodeRegister(sm.str(1), inst.op1)) {
			return true;
		} else {
			return false;
		}
	} else if (regex_match(line, sm, dec_template)) {
		inst.inst_type = INST_DEC;

		if (DecodeRegister(sm.str(1), inst.op1)) {
			return true;
		} else {
			return false;
		}
	} else if (regex_match(line, sm, jnz1_template)) {
		inst.inst_type = INST_JNZ;

		if (DecodeRegister(sm.str(1), inst.op1)) {
			if (DecodeRegister(sm.str(2), inst.op2)) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (regex_match(line, sm, jnz2_template)) {
		inst.inst_type = INST_JNZ;
		inst.op2_is_register = false;

		inst.op2 = atoi(sm.str(2).c_str());

		if (DecodeRegister(sm.str(1), inst.op1)) {
			return true;
		} else {
			return false;
		}
	} else if (regex_match(line, sm, jnz3_template)) {
		inst.inst_type = INST_JNZ;
		inst.op1_is_register = false;

		inst.op1 = atoi(sm.str(1).c_str());

		if (DecodeRegister(sm.str(2), inst.op2)) {
			return true;
		} else {
			return false;
		}
	} else if (regex_match(line, sm, jnz4_template)) {
		inst.inst_type = INST_JNZ;
		inst.op1_is_register = false;
		inst.op2_is_register = false;

		inst.op1 = atoi(sm.str(1).c_str());
		inst.op2 = atoi(sm.str(2).c_str());

		return true;
	}

	return false;
}
void Trace(std::vector<INSTRUCTION> prg, int c_value, int &result1) {
	int regs[4] = {0, 0, 0, 0};
	int pc = 0, val;

	regs[REG_C_IDX] = c_value;

	while ((pc >= 0) && (pc < prg.size())) {
		switch (prg[pc].inst_type) {
			case INST_CPY:
				if (prg[pc].op2_is_register) {
					if (prg[pc].op1_is_register) {
						regs[prg[pc].op2] = regs[prg[pc].op1];
					} else {
						regs[prg[pc].op2] = prg[pc].op1;
					}
				}
				pc++;
				break;

			case INST_INC:
				if (prg[pc].op1_is_register) {
					regs[prg[pc].op1]++;
				}
				pc++;
				break;

			case INST_DEC:
				if (prg[pc].op1_is_register) {
					regs[prg[pc].op1]--;
				}
				pc++;
				break;

			case INST_JNZ:
				if (prg[pc].op1_is_register) {
					val = regs[prg[pc].op1];
				} else {
					val = prg[pc].op1;
				}
				if (val) {
					if (prg[pc].op2_is_register) {
						pc += regs[prg[pc].op2];
					} else {
						pc += prg[pc].op2;
					}
				} else {
					pc++;
				}
				break;
		}
	}

	result1 = regs[REG_A_IDX];
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

		if (!DecodeInstruction(line, instruction)) {
			std::cout << "Invalid instruction at line " << cnt << std::endl;
			return -1;
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
