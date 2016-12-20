#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

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
	int	repeat_len, repeat_cnt;
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


int main(void) {
	std::ifstream input;
	std::string line, packed;
	long long result1, result2;
	bool packed_data_found;

	std::cout << "=== Advent of Code 2016 - day 9 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	//input.open("input-test.txt", std::ifstream::in);
	//input.open("input-test2.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	packed.clear();

	while (std::getline(input, line)) {
		packed += line;
	}

	if (!Unpack(packed, result1, result2)){
		return -1;
	}

	/*
	result1 = 0;
	result2 = 0;
	packed = "(3x3)XYZ";
	Unpack(packed, result1, result2);

	result1 = 0;
	result2 = 0;
	packed = "X(8x2)(3x3)ABCY";
	Unpack(packed, result1, result2);

	result1 = 0;
	result2 = 0;
	packed = "(27x12)(20x12)(13x14)(7x10)(1x12)A";
	Unpack(packed, result1, result2);

	result1 = 0;
	result2 = 0;
	packed = "(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN";
	Unpack(packed, result1, result2);
*/

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
