
#include <cstring>
#include <iostream>
//#include <fstream>
//#include <map>
//#include <regex>
//#include <string>
//#include <vector>

#define TEST 1
#define FIRST_FLOOR 1
#define FINAL_FLOOR 4

#define GENERATOR 0
#define MICROCHIP 1
const std::string type_names[] = {"Genr", "Chip"};
const std::string empty_type_name = "....";

#define HYDROGEN 0
#define LITHIUM 1

int result1, result2;

#ifdef TEST
const int MAX_RTG_TYPES = 2;
const std::string names[MAX_RTG_TYPES] = {"Hydr", "Lith"};
const std::string empty_name = "....";
const int init_map[MAX_RTG_TYPES][2] = {{2, 1}, {3, 1}};
#else
#endif

void DescribeState(const int current_map[MAX_RTG_TYPES][2], int elevator) {
	std::cout << std::endl;
	for (int i = FINAL_FLOOR; i >= FIRST_FLOOR; i--) {
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

bool IsStateValid(const int current_map[MAX_RTG_TYPES][2]) {
	bool single_gen, single_chip;

	for (int i = FIRST_FLOOR; i <= FINAL_FLOOR; i++) {
		single_gen = single_chip = false;

		for (int j = 0; j < MAX_RTG_TYPES; j++) {
			if ((current_map[j][0] == i) && (current_map[j][1] != i)) {
				single_gen = true;
			}
			if ((current_map[j][0] != i) && (current_map[j][1] == i)) {
				single_chip = true;
			}
		}
		if (single_gen && single_chip) {
			return false;
		}
	}

	return true;
}

bool IsFinished(const int current_map[MAX_RTG_TYPES][2]) {
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		for (int k = 0; k < 2; k++) {
			if (current_map[j][k] != FINAL_FLOOR) {
				return false;
			}
		}
	}
	return true;
}

void DoMove(const int current_map[MAX_RTG_TYPES][2], int curr_elevator, int curr_steps, int& steps_limit) {
	curr_steps++;
	int next_map[MAX_RTG_TYPES][2];
	int next_elevator;

	if (curr_steps >= steps_limit) {
		return;
	}

	if (IsFinished(current_map)){
		steps_limit = curr_steps;
		return;
	}
///
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		for (int k = 0; k < 2; k++) {
			next_map[j][k] = current_map[j][k];
		}
	}
	next_elevator = curr_elevator;
	DoMove(next_map, next_elevator, curr_steps, steps_limit);
	///
}

int main(void) {
	int cnt;
	int current_map[MAX_RTG_TYPES][2];

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		for (int k = 0; k < 2; k++) {
			current_map[j][k] = init_map[j][k];
		}
	}

	result1 = 1000000;
	result2 = 0;
	cnt = 0;

	//DescribeState(current_map, 1);

	bool res = IsStateValid(current_map);

	res = IsFinished(current_map);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
