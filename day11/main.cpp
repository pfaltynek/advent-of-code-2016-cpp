
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
typedef struct {
	int Gen;
	int Chip;
} RTG_PAIR;

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

void DescribeState(const RTG_PAIR current_map[MAX_RTG_TYPES], int elevator) {
	std::cout << std::endl;
	for (int i = FINAL_FLOOR; i >= FIRST_FLOOR; i--) {
		std::cout << 'F' << i << ' ';
		if (elevator == i) {
			std::cout << "E ";
		} else {
			std::cout << ". ";
		}
		for (int j = 0; j < MAX_RTG_TYPES; j++) {
			if (current_map[j].Gen == i) {
				std::cout << names[j].c_str() << type_names[GENERATOR].c_str();
			} else {
				std::cout << empty_name.c_str() << empty_type_name.c_str();
			}

			std::cout << ' ';

			if (current_map[j].Chip == i) {
				std::cout << names[j].c_str() << type_names[MICROCHIP].c_str();
			} else {
				std::cout << empty_name.c_str() << empty_type_name.c_str();
			}

			std::cout << ' ';
		}
	}
	std::cout << std::endl;
}

bool IsStateValid(const RTG_PAIR current_map[MAX_RTG_TYPES]) {
	bool single_gen, single_chip;

	for (int i = FIRST_FLOOR; i <= FINAL_FLOOR; i++) {
		single_gen = single_chip = false;

		for (int j = 0; j < MAX_RTG_TYPES; j++) {
			if ((current_map[j].Gen == i) && (current_map[j].Chip != i)) {
				single_gen = true;
			}
			if ((current_map[j].Gen != i) && (current_map[j].Chip == i)) {
				single_chip = true;
			}
		}
		if (single_gen && single_chip) {
			return false;
		}
	}

	return true;
}

bool IsFinished(const RTG_PAIR current_map[MAX_RTG_TYPES]) {
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		if ((current_map[j].Gen != FINAL_FLOOR) || (current_map[j].Chip != FINAL_FLOOR)) {
			return false;
		}
	}
	return true;
}

void MapCopy(const RTG_PAIR current_map[MAX_RTG_TYPES], RTG_PAIR next_map[MAX_RTG_TYPES]) {
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		next_map[j] = current_map[j];
	}
}

void DoMove(const RTG_PAIR current_map[MAX_RTG_TYPES], int curr_elevator, int curr_steps, int &steps_limit) {
	RTG_PAIR next_map[MAX_RTG_TYPES];
	int curr_floor_map[MAX_RTG_TYPES * 2][2];
	int curr_floor_map_size;
	int next_elevator;

	curr_steps++;

	if (curr_steps >= steps_limit) {
		return;
	}

	if (IsFinished(current_map)) {
		steps_limit = curr_steps;
		return;
	}

/*
	curr_floor_map_size = 0;
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		for (int k = 0; k < 2; k++) {
			if (current_map[j][k] == curr_elevator) {
				curr_floor_map[curr_floor_map_size][0] = j;
				curr_floor_map[curr_floor_map_size][1] = k;
				curr_floor_map_size++;
			}
		}
	}

	for (int i = 0; i < curr_floor_map_size; i++) {
		if (curr_elevator > FIRST_FLOOR) {
			next_elevator = curr_elevator - 1;
			MapCopy(current_map, next_map);
			next_map[curr_floor_map[i][0]][curr_floor_map[i][1]] = next_elevator;
			if (IsStateValid(next_map)) {
				DoMove(next_map, next_elevator, curr_steps, steps_limit);
			}

			for (int j = i + 1; j < curr_floor_map_size; j++) {
				MapCopy(current_map, next_map);
				next_map[curr_floor_map[i][0]][curr_floor_map[i][1]] = next_elevator;
				next_map[curr_floor_map[j][0]][curr_floor_map[j][1]] = next_elevator;
				if (IsStateValid(next_map)) {
					DoMove(next_map, next_elevator, curr_steps, steps_limit);
				}
			}
		}
		if (curr_elevator < FINAL_FLOOR) {
			next_elevator = curr_elevator + 1;
			MapCopy(current_map, next_map);
			next_map[curr_floor_map[i][0]][curr_floor_map[i][1]] = next_elevator;
			if (IsStateValid(next_map)) {
				DoMove(next_map, next_elevator + 1, curr_steps, steps_limit);
			}

			for (int j = i + 1; j < curr_floor_map_size; j++) {
				MapCopy(current_map, next_map);
				next_map[curr_floor_map[i][0]][curr_floor_map[i][1]] = next_elevator;
				next_map[curr_floor_map[j][0]][curr_floor_map[j][1]] = next_elevator;
				if (IsStateValid(next_map)) {
					DoMove(next_map, next_elevator, curr_steps, steps_limit);
				}
			}
		}
	}
	*/
}

int main(void) {
	int cnt;
	RTG_PAIR current_map[MAX_RTG_TYPES];

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		current_map[j].Gen = init_map[j][GENERATOR];
		current_map[j].Chip = init_map[j][MICROCHIP];
	}

	result1 = 1000000;
	result2 = 0;
	cnt = 0;

	//DoMove(current_map, 1, 0, result1);

	//DescribeState(current_map, 1);

	//bool res = IsStateValid(current_map);

	//res = IsFinished(current_map);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
