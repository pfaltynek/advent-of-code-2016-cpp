#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define TEST 1

typedef struct {
	uint32_t first, last;
} IP_RANGE;

void InsertRange(IP_RANGE new_range, std::vector<IP_RANGE> &ranges) {


}

uint32_t GetFirstWhiteIP(std::vector<IP_RANGE> ranges) {
	
	return 0;
}

int main(void) {
	std::ifstream input;
	std::string line;
	uint32_t result1, result2, test, cnt;
	std::regex data_pattern("^(\\d+)-(\\d+)$");
	std::smatch sm;
	std::vector<IP_RANGE> data;
	IP_RANGE x;

	std::cout << "=== Advent of Code 2016 - day 20 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	test = 0;
	cnt = 0;

#if TEST
	data.clear();
	x.first = 5;
	x.last = 8;
	InsertRange(x, data);
	data.push_back(x);
	x.first = 0;
	x.last = 2;
	InsertRange(x, data);
	x.first = 4;
	x.last = 7;
	InsertRange(x, data);
	test = GetFirstWhiteIP(data);
#endif

	data.clear();

	while (std::getline(input, line)) {
		cnt++;
		if (line.empty()) {
			continue;
		}
		if (regex_match(line, sm, data_pattern)) {
			IP_RANGE ipr;

			ipr.first = (uint32_t)atol(sm.str(1).c_str());
			ipr.last = (uint32_t)atol(sm.str(2).c_str());
			InsertRange(x, data);
		} else {
			std::cout << "Error decoding data of line " << cnt << std::endl;
			return -1;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = GetFirstWhiteIP(data);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	result2 = GetFirstWhiteIP(data);
	std::cout << "Result is " << result2 << std::endl;
}
