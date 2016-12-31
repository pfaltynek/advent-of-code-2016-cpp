//#include <cstring>
//#include <fstream>
#include <iostream>
//#include <map>
//#include <regex>
//#include <string>
//#include <vector>

//#define TEST 1

#ifdef TEST
const int max_rtg_types = 3;
const char names[max_rtg_types][] = {"hydrogen", "lithium", "test"};
const char init_map[4][max_rtg_types * 2] = {}
#else
const int part1_val1 = 61;
const int part1_val2 = 17;
const std::string input_filename = "input.txt";
#endif

int elevator = 0;

int main(void) {
	int result1, result2, cnt;

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = 0;
	result2 = 0;
	cnt = 0;

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
