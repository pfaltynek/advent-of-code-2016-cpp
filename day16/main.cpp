#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

const int disk1size = 272;
const int disk2size = 35651584;

#define TEST 0//1

std::string GetDragonChecksum(std::string source, int size) {
	std::string data = source;
	std::string second;

	while (data.size() < size) {
		second = "0";
		for (std::string::reverse_iterator rit = data.rbegin(); rit != data.rend(); ++rit) {
			second += (*rit == '0' ? '1' : '0');
		}
		data += second;
	}
	data = data.substr(0, size);

	do {
		second.clear();
		for (int i = 0; i < (data.size() / 2); i++) {
			second += (data[2 * i] == data[(2 * i) + 1]) ? '1' : '0';
		}
		data = second;
	} while ((second.size() % 2) == 0);

	return second;
}

int main(void) {
	std::ifstream input;
	std::string line, data, result1, result2;

	std::cout << "=== Advent of Code 2016 - day 16 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

#if TEST
	result1 = GetDragonChecksum("10000", 20);
	result1 = GetDragonChecksum("110010110100", 12);
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
	std::cout << "Result is:" << result2 << std::endl;
}
