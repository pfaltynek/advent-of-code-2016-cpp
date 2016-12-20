#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

std::regex regex_number("\\d+");

bool DecodeMarker(std::string marker, int &length, int &count) {
	std::regex regex_number("\\d+");
	std::smatch sm;

	if (regex_search(marker, sm, regex_number)) {
		length = atoi(sm[0].str().c_str());
		marker = sm.suffix().str();

		if (regex_search(marker, sm, regex_number)) {
			count = atoi(sm[0].str().c_str());
			return true;
		}
	}

	return false;
}

bool Unpack(std::string &input, long long &format1size, long long &format2size) {
	long long cnt1, cnt2;
	int repeat_len, repeat_cnt;
	std::regex regex_marker("[(]\\d+[xX]\\d+[)]");
	std::smatch sm;
	std::string marker, block;

	while (regex_search(input, sm, regex_marker)) {
		format1size += sm.prefix().str().size();
		format2size += sm.prefix().str().size();

		marker = sm[0];

		if (!DecodeMarker(marker, repeat_len, repeat_cnt)) {
			return false;
		}
		input = sm.suffix().str();
		block = input.substr(0, repeat_len);
		input = input.substr(repeat_len);
		format1size += repeat_len * repeat_cnt;
		cnt1 = 0;
		cnt2 = 0;
		if (!Unpack(block, cnt1, cnt2)) {
			return false;
		}
		format2size += repeat_cnt * cnt2;
	}
	format1size += input.size();
	format2size += input.size();

	return true;
}

bool DecodeValueInstruction(std::string instruction, int &value, int &bot) {
	std::regex value_template("value \\d+ goes to bot \\d+");
	std::smatch sm;

	if (regex_search(instruction, sm, value_template)) {
		if (regex_search(instruction, sm, regex_number)) {
			value = atoi(sm[0].str().c_str());
			
			return true;
		}
	}
	return false;
}

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, result2, cnt, val1, val2, bot_number;
	std::map<int, int> values;

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
		cnt++;
		switch (line[0]) {
			case 'v':
				if (DecodeValueInstruction(line, val1, bot_number)) {
					values[bot_number] = val1;
				} else {
					return -1;
				}
				break;
			case 'b':

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
