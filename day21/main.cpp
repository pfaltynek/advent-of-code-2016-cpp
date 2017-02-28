#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

//#define TEST 1
//#define LOG 1

typedef enum {
	SWAP_POS,
	SWAP_LETTER,
	ROT_LEFT,
	ROT_RIGHT,
	ROT_BY_LETTER_POS,
	REVERSE,
	MOVE_POS2POS
} DAY_21_INST_TYPE;

typedef struct {
	int par1, par2;
	DAY_21_INST_TYPE inst_type;
} DAY21_INST;

std::regex swap_position_regex("^swap position (\\d+) with position (\\d+)$");
std::regex swap_letter_regex("^swap letter (.) with letter (.)$");
std::regex rotate_right_regex("^rotate right (\\d+) (step|steps)$");
std::regex rotate_left_regex("^rotate left (\\d+) (step|steps)$");
std::regex rotate_by_letter_pos_regex("^rotate based on position of letter (.)$");
std::regex reverse_regex("^reverse positions (\\d+) through (\\d+)$");
std::regex move_pos2pos_regex("^move position (\\d+) to position (\\d+)$");

bool DecodeInstruction(std::string line, DAY21_INST &inst) {
	std::smatch sm;

	if (std::regex_match(line, sm, swap_position_regex)) {
		inst.inst_type = SWAP_POS;
		inst.par1 = atoi(sm.str(1).c_str());
		inst.par2 = atoi(sm.str(2).c_str());
		return true;
	}
	if (std::regex_match(line, sm, swap_letter_regex)) {
		inst.inst_type = SWAP_LETTER;
		inst.par1 = sm.str(1).c_str()[0];
		inst.par2 = sm.str(2).c_str()[0];
		return true;
	}
	if (std::regex_match(line, sm, rotate_right_regex)) {
		inst.inst_type = ROT_RIGHT;
		inst.par1 = atoi(sm.str(1).c_str());
		return true;
	}
	if (std::regex_match(line, sm, rotate_left_regex)) {
		inst.inst_type = ROT_LEFT;
		inst.par1 = atoi(sm.str(1).c_str());
		return true;
	}

	if (std::regex_match(line, sm, rotate_by_letter_pos_regex)) {
		inst.inst_type = ROT_BY_LETTER_POS;
		inst.par1 = sm.str(1).c_str()[0];
		return true;
	}

	if (std::regex_match(line, sm, reverse_regex)) {
		inst.inst_type = REVERSE;
		inst.par1 = atoi(sm.str(1).c_str());
		inst.par2 = atoi(sm.str(2).c_str());
		return true;
	}

	if (std::regex_match(line, sm, move_pos2pos_regex)) {
		inst.inst_type = MOVE_POS2POS;
		inst.par1 = atoi(sm.str(1).c_str());
		inst.par2 = atoi(sm.str(2).c_str());
		return true;
	}

	return false;
}

void LogInstruction(DAY21_INST inst) {
	switch (inst.inst_type) {
		case SWAP_POS:
			std::cout << "Swap positions " << inst.par1 << " & " << inst.par2;
			break;
		case SWAP_LETTER:
			std::cout << "Swap letters " << (char)inst.par1 << " & " << (char)inst.par2;
			break;
		case ROT_LEFT:
			std::cout << "Rotate left " << inst.par1;
			break;
		case ROT_RIGHT:
			std::cout << "Rotate right " << inst.par1;
			break;
		case ROT_BY_LETTER_POS:
			std::cout << "Rotate right by index of letter " << (char)inst.par1;
			break;
		case REVERSE:
			std::cout << "Reverse from " << inst.par1 << " to " << inst.par2;
			break;
		case MOVE_POS2POS:
			std::cout << "Move from position " << inst.par1 << " to " << inst.par2;
			break;
		default:
			int z = 11;
			break;
	}
	std::cout << std::endl;
}

void ScramblePassword(std::string &password, std::vector<DAY21_INST> insts) {
	std::vector<DAY21_INST>::iterator it;
	std::string test = password;

	for (it = insts.begin(); it != insts.end(); ++it) {

#if LOG
		std::cout << password.c_str() << " -> ";
#endif

		switch (it->inst_type) {
			case SWAP_POS:
				if ((it->par1 >= 0) && (it->par2 >= 0) && (it->par1 < password.size()) && (it->par2 < password.size())) {
					char tmp;
					tmp = password[it->par1];
					password[it->par1] = password[it->par2];
					password[it->par2] = tmp;
				} else {
					int z = 0;
				}
				break;
			case SWAP_LETTER:
				char c1, c2;
				c1 = (char)it->par1;
				c2 = (char)it->par2;
				for (int i = 0; i < password.size(); i++) {
					if (password[i] == c1) {
						password[i] = c2;
					} else if (password[i] == c2) {
						password[i] = c1;
					}
				}
				break;
			case ROT_LEFT:
				if (it->par1 == 0) {
					break;
				}
				if (it->par1 > 0) {
					int shift = it->par1 % password.size();

					password = password.substr(shift) + password.substr(0, shift);
				} else {
					int x = 11;
				}
				break;
			case ROT_RIGHT:
				if (it->par1 == 0) {
					break;
				}
				if (it->par1 > 0) {
					int shift = it->par1 % password.size();

					password = password.substr(password.size() - shift) + password.substr(0, password.size() - shift);
				} else {
					int x = 11;
				}
				break;
			case ROT_BY_LETTER_POS:
				size_t pos;
				pos = password.find((char)it->par1);

				if (pos != std::string::npos) {
					pos += (pos >= 4) ? 2 : 1;
					pos = pos % password.size();
					if (pos > 0) {
						password = password.substr(password.size() - pos) + password.substr(0, password.size() - pos);
					}
				} else {
					int x = 26;
				}
				break;
			case REVERSE:
				if ((it->par1 >= 0) && (it->par2 >= 0) && (it->par1 < password.size()) && (it->par2 < password.size())) {
					for (int i = 0; i < ((it->par2 - (it->par1 - 1)) / 2); i++) {
						char x = password[(it->par2) - i];
						password[(it->par2) - i] = password[(it->par1) + i];
						password[(it->par1) + i] = x;
					}
				} else {
					int u = 13;
				}
				break;
			case MOVE_POS2POS:
				if ((it->par1 >= 0) && (it->par2 >= 0) && (it->par1 < password.size()) && (it->par2 < password.size())) {
					char x = password[it->par1];

					password.erase(it->par1, 1);
					password.insert(password.begin() + it->par2, x);
				} else {
					int i = 11;
				}
				break;
			default:
				int x = 11;
				break;
		}
#if LOG
		std::cout << password.c_str() << std::endl;
#endif
	}
}

void FillPasswordsForBF(std::string password, std::string item, std::vector<std::string> &list) {
	std::string::iterator it;

	if (password.empty()) {
		list.push_back(item);
		return;
	}

	for (int i = 0; i < password.size(); i++) {
		std::string new_pwd = password;
		new_pwd.erase(i, 1);
		FillPasswordsForBF(new_pwd, item + password[i], list);
	}
}

void UnScramblePasswordBF(std::string &password, std::vector<DAY21_INST> insts) {
	std::vector<std::string> bf_source;
	std::string result;

	bf_source.clear();
	FillPasswordsForBF(password, "", bf_source);
	for (int i = 0; i < bf_source.size(); i++) {
		result = bf_source[i];
		ScramblePassword(result, insts);
		if (result == password) {
			password = bf_source[i];
			break;
		}
	}
}

int main(void) {
	std::ifstream input;
	std::string line, result1, result2;
	std::vector<DAY21_INST> data;
	int cnt;

	cnt = 0;
	result1.clear();
	result2.clear();

	std::cout << "=== Advent of Code 2016 - day 21 ====" << std::endl;

#if TEST
	input.open("input-test.txt", std::ifstream::in);
#else
	input.open("input.txt", std::ifstream::in);
#endif

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	data.clear();

#if LOG
	std::cout << "Instructions:" << std::endl;
#endif

	while (std::getline(input, line)) {
		DAY21_INST inst;
		cnt++;
		if (DecodeInstruction(line, inst)) {
			data.push_back(inst);
#if LOG
			std::cout << cnt << ". ";
			LogInstruction(inst);
#endif
		} else {
			std::cout << "Unknown instruction at line " << cnt << std::endl;
			return -1;
		}
	}

	if (input.is_open()) {
		input.close();
	}

#if TEST
	std::cout << "--- test ---" << std::endl;
	result1 = "abcde";
	ScramblePassword(result1, data);
	std::cout << "Result is " << result1 << std::endl;
#else
	std::cout << "--- part 1 ---" << std::endl;
	result1 = "abcdefgh";
	ScramblePassword(result1, data);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	result2 = "fbgdceah";
	UnScramblePasswordBF(result2, data);
	std::cout << "Result is " << result2 << std::endl;
#endif
}
