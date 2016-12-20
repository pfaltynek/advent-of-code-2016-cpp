#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

std::regex regex_number("\\d+");

typedef enum { OUT_EMPTY,
			   OUT_BOT,
			   OUT_OUTPUT } OUT_TYPE;

typedef struct {
	int bot, low, high;
	OUT_TYPE low_type, high_type;
} BOT_INSTRUCTION;

bool DecodeBotInstruction(std::string instruction, BOT_INSTRUCTION &info) {
	std::regex bot_template("bot \\d+ gives low to (bot|output) \\d+ and high to (bot|output) \\d+");
	std::regex low_bot("gives low to bot");
	std::regex low_output("gives low to output");
	std::regex high_bot("and high to bot");
	std::regex high_output("and high to output");
	std::smatch sm;
	int bot_number;

	if (regex_search(instruction, sm, bot_template)) {
		if (regex_search(instruction, sm, regex_number)) {
			bot_number = atoi(sm[0].str().c_str());
			instruction = sm.suffix().str();

			return true;
		}
	}

	return false;
}

bool DecodeValueInstruction(std::string instruction, int &value, int &bot) {
	std::regex value_template("value \\d+ goes to bot \\d+");
	std::smatch sm;

	if (regex_search(instruction, sm, value_template)) {
		if (regex_search(instruction, sm, regex_number)) {
			value = atoi(sm[0].str().c_str());
			instruction = sm.suffix().str();
			if (regex_search(instruction, sm, regex_number)) {
				bot = atoi(sm[0].str().c_str());
				return true;
			}
		}
	}
	return false;
}

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, result2, cnt, val1, val2, bot_number;
	std::map<int, std::vector<int>> values;

	std::cout << "=== Advent of Code 2016 - day 10 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	//input.open("input-test.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	cnt = 0;

	while (std::getline(input, line)) {
		BOT_INSTRUCTION info;

		cnt++;
		switch (line[0]) {
			case 'v':
				if (DecodeValueInstruction(line, val1, bot_number)) {
					if (values.find(bot_number) == values.end()) {
						std::vector<int> list;

						list.push_back(val1);
						values[bot_number] = list;
					} else {
						values[bot_number].push_back(val1);
					}

				} else {
					return -1;
				}
				break;
			case 'b':
				info.low_type = OUT_EMPTY;
				info.high_type = OUT_EMPTY;
				if (DecodeBotInstruction(line, info)) {

				} else {
					return -1;
				}
				break;
			default:
				std::cout << "Invalid instruction on line " << cnt << std::endl;
				return -1;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
