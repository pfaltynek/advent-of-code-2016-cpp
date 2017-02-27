#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define TEST 1

const char tile_safe = '.';
const char tile_trap = '^';

int GetSafeTilesOfRowCount(std::string line) {
	int result = 0;

	for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
		if (*it == tile_safe) {
			result++;
		}
	}
	return result;
}

std::string GetNextRoomLine(std::string prev_line) {
	std::string result = "";
	std::string tmp;

	tmp.push_back(tile_safe);
	tmp += prev_line;
	tmp.push_back(tile_safe);

	for (int i = 1; i < (tmp.size() - 1); i++) {
		if (tmp[i - 1] != tmp[i + 1]) {
			result.push_back(tile_trap);
		} else {
			result.push_back(tile_safe);
		}
	}

	return result;
}

int GetSafeTilesOfRoomCount(std::string first_line, int total_lines) {
	int lines_cnt = 1;
	int result = 0;
	std::string prev_line = first_line;

	result = GetSafeTilesOfRowCount(prev_line);
	while (lines_cnt < total_lines) {
		prev_line = GetNextRoomLine(prev_line);
		result += GetSafeTilesOfRowCount(prev_line);
		lines_cnt++;
	}

	return result;
}

int main(void) {
	std::ifstream input;
	std::string line, data;
	int test, result1, result2;

	std::cout << "=== Advent of Code 2016 - day 18 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	data.clear();

	while (std::getline(input, line)) {
		data += line;
	}

	if (input.is_open()) {
		input.close();
	}

#if TEST
	test = GetSafeTilesOfRoomCount("..^^.", 3);
	test = GetSafeTilesOfRoomCount(".^^.^.^^^^", 10);
#endif

	result1 = GetSafeTilesOfRoomCount(data, 40);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	result2 = GetSafeTilesOfRoomCount(data, 400000);
	std::cout << "Result is " << result2 << std::endl;
}
