
#include <iostream>
#include <cstring>
//#include <fstream>
//#include <map>
//#include <regex>
//#include <string>
//#include <vector>

#define TEST 1
#define GENERATOR 0
#define MICROCHIP 1
const std::string type_names[] = {"Genr", "Chip"};
const std::string empty_type_name = "....";

#define HYDROGEN 0
#define LITHIUM 1

int elevator = 1;
int result1, result2;

#ifdef TEST
const int MAX_RTG_TYPES = 2;
const std::string names[MAX_RTG_TYPES] = {"Hydr", "Lith"};
const std::string empty_name = "....";
#else
#endif

void DescribeState(const int current_map[MAX_RTG_TYPES][2]) {
	std::cout << std::endl;
	for (int i = 4; i >= 1; i--) {
		std::cout << 'F' << i << ' ';
		if (elevator == i) {
			std::cout << "E ";
		} else {
			std::cout << ". ";
		}
		for (int j = 0; j < MAX_RTG_TYPES; j++) {
			for (int k = 0; k < 2; k++) {
				if (current_map[j][k] == i) {
					std::cout << names[j].c_str() << type_names[k].c_str();
				} else {
					std::cout << empty_name.c_str() << empty_type_name.c_str();
				}
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}

int main(void) {
	int cnt;

#ifdef TEST
	const int init_map[MAX_RTG_TYPES][2] = {{2, 1}, {3, 1}};
#else
#endif

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1 = 0;
	result2 = 0;
	cnt = 0;
	elevator = 1;

	DescribeState(init_map);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
