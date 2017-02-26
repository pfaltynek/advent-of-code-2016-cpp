#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define TEST 1

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

std::regex swap_position_regex("swap position (\\d+) with position (\\d+)");
std::regex swap_letter_regex("swap letter (.) with letter (.)");
std::regex swap_position_regex("rotate (left|right) (\\d+) steps");
std::regex swap_position_regex("rotate based on position of letter (.)");
std::regex swap_position_regex("reverse positions (\\d+) through (\\d+)");
std::regex swap_position_regex("move position (\\d+) to position (\\d+)");

int main(void) {
	std::ifstream input;
	std::string line, data, result1, result2;

	std::cout << "=== Advent of Code 2016 - day 21 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

#if TEST
	input.open("input-test.txt", std::ifstream::in);
#else
	input.open("input.txt", std::ifstream::in);
#endif

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

#if TEST

#endif

	data.clear();

	while (std::getline(input, line)) {
		data += line;
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = GetDragonChecksum(data, disk1size);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	result2 = GetDragonChecksum(data, disk2size);
	std::cout << "Result is " << result2 << std::endl;
}
