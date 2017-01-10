

#include <cstring>
#include <iostream>
//#include <fstream>
//#include <map>
//#include <regex>
//#include <string>
#include <vector>

#define TEST 1
#define FIRST_FLOOR 1
#define FINAL_FLOOR 4

#define GENERATOR 0
#define MICROCHIP 1

#ifdef TEST
const int MAX_RTG_TYPES = 2;
const std::string names[MAX_RTG_TYPES] = {"Hydr", "Lith"};
const std::string empty_name = "....";
const int init_map[MAX_RTG_TYPES][2] = {{2, 1}, {3, 1}};
#else
#endif

typedef struct {
	int Gen;
	int Chip;
} RTG_PAIR;

typedef struct {
	RTG_PAIR map[MAX_RTG_TYPES];
	int elevator;
} HOUSE_MAP;

const std::string type_names[] = {"Genr", "Chip"};
const std::string empty_type_name = "....";

#define HYDROGEN 0
#define LITHIUM 1

int result1, result2;

void DescribeState(const HOUSE_MAP current_map) {
	std::cout << std::endl;
	for (int i = FINAL_FLOOR; i >= FIRST_FLOOR; i--) {
		std::cout << 'F' << i << ' ';
		if (current_map.elevator == i) {
			std::cout << "E ";
		} else {
			std::cout << ". ";
		}
		for (int j = 0; j < MAX_RTG_TYPES; j++) {
			if (current_map.map[j].Gen == i) {
				std::cout << names[j].c_str() << type_names[GENERATOR].c_str();
			} else {
				std::cout << empty_name.c_str() << empty_type_name.c_str();
			}

			std::cout << ' ';

			if (current_map.map[j].Chip == i) {
				std::cout << names[j].c_str() << type_names[MICROCHIP].c_str();
			} else {
				std::cout << empty_name.c_str() << empty_type_name.c_str();
			}

			std::cout << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool IsStateValid(const HOUSE_MAP current_map) {
	bool single_gen, single_chip;

	for (int i = FIRST_FLOOR; i <= FINAL_FLOOR; i++) {
		single_gen = single_chip = false;

		for (int j = 0; j < MAX_RTG_TYPES; j++) {
			if ((current_map.map[j].Gen == i) && (current_map.map[j].Chip != i)) {
				single_gen = true;
			}
			if ((current_map.map[j].Gen != i) && (current_map.map[j].Chip == i)) {
				single_chip = true;
			}
		}
		if (single_gen && single_chip) {
			return false;
		}
	}

	return true;
}

bool IsFinished(const HOUSE_MAP current_map) {
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		if ((current_map.map[j].Gen != FINAL_FLOOR) || (current_map.map[j].Chip != FINAL_FLOOR)) {
			return false;
		}
	}
	return true;
}

void MapCopy(const HOUSE_MAP current_map, HOUSE_MAP &next_map) {
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		next_map.map[j] = current_map.map[j];
	}
	next_map.elevator = current_map.elevator;
}

void DoMove(const HOUSE_MAP current_map, int curr_steps, int &steps_limit, std::vector<HOUSE_MAP> history) {
	HOUSE_MAP next_map;
	int curr_floor_map[MAX_RTG_TYPES * 2][2];
	int curr_floor_map_size;
	int next_elevator;

	curr_steps++;
	history.push_back(current_map);

	if (curr_steps >= steps_limit) {
		return;
	}

	if (IsFinished(current_map)) {
		steps_limit = curr_steps;

		for (int i = 0; i < history.size(); i++) {
			DescribeState(history[i]);
		}
		return;
	}

	curr_floor_map_size = 0;
	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		if (current_map.map[j].Gen == current_map.elevator) {
			curr_floor_map[curr_floor_map_size][0] = j;
			curr_floor_map[curr_floor_map_size][1] = GENERATOR;
			curr_floor_map_size++;
		}
		if (current_map.map[j].Chip == current_map.elevator) {
			curr_floor_map[curr_floor_map_size][0] = j;
			curr_floor_map[curr_floor_map_size][1] = MICROCHIP;
			curr_floor_map_size++;
		}
	}

	for (int i = 0; i < curr_floor_map_size; i++) {
		if (current_map.elevator > FIRST_FLOOR) {
			next_elevator = current_map.elevator - 1;
			MapCopy(current_map, next_map);
			next_map.elevator = next_elevator;
			if (curr_floor_map[i][1] == GENERATOR) {
				next_map.map[curr_floor_map[i][0]].Gen = next_elevator;
			} else {
				next_map.map[curr_floor_map[i][0]].Chip = next_elevator;
			}
			if (IsStateValid(next_map)) {
				std::vector<HOUSE_MAP> new_hist(history);
				DoMove(next_map, curr_steps, steps_limit, new_hist);
			}

			for (int j = i + 1; j < curr_floor_map_size; j++) {
				MapCopy(current_map, next_map);
				next_map.elevator = next_elevator;
				if (curr_floor_map[i][1] == GENERATOR) {
					next_map.map[curr_floor_map[i][0]].Gen = next_elevator;
				} else {
					next_map.map[curr_floor_map[i][0]].Chip = next_elevator;
				}
				if (curr_floor_map[j][1] == GENERATOR) {
					next_map.map[curr_floor_map[j][0]].Gen = next_elevator;
				} else {
					next_map.map[curr_floor_map[j][0]].Chip = next_elevator;
				}
				if (IsStateValid(next_map)) {
					std::vector<HOUSE_MAP> new_hist(history);
					DoMove(next_map, curr_steps, steps_limit, new_hist);
				}
			}
		}

		if (current_map.elevator < FINAL_FLOOR) {
			next_elevator = current_map.elevator + 1;
			MapCopy(current_map, next_map);
			next_map.elevator = next_elevator;
			if (curr_floor_map[i][1] == GENERATOR) {
				next_map.map[curr_floor_map[i][0]].Gen = next_elevator;
			} else {
				next_map.map[curr_floor_map[i][0]].Chip = next_elevator;
			}
			if (IsStateValid(next_map)) {
				std::vector<HOUSE_MAP> new_hist(history);
				DoMove(next_map, curr_steps, steps_limit, new_hist);
			}

			for (int j = i + 1; j < curr_floor_map_size; j++) {
				MapCopy(current_map, next_map);
				next_map.elevator = next_elevator;
				if (curr_floor_map[i][1] == GENERATOR) {
					next_map.map[curr_floor_map[i][0]].Gen = next_elevator;
				} else {
					next_map.map[curr_floor_map[i][0]].Chip = next_elevator;
				}
				if (curr_floor_map[j][1] == GENERATOR) {
					next_map.map[curr_floor_map[j][0]].Gen = next_elevator;
				} else {
					next_map.map[curr_floor_map[j][0]].Chip = next_elevator;
				}
				if (IsStateValid(next_map)) {
					std::vector<HOUSE_MAP> new_hist(history);
					DoMove(next_map, curr_steps, steps_limit, new_hist);
				}
			}
		}
	}
}

int main(void) {
	int cnt;
	HOUSE_MAP current_map;
	std::vector<HOUSE_MAP> history;

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	for (int j = 0; j < MAX_RTG_TYPES; j++) {
		current_map.map[j].Gen = init_map[j][GENERATOR];
		current_map.map[j].Chip = init_map[j][MICROCHIP];
	}
	current_map.elevator = 1;

	result1 = 12;
	result2 = 0;
	cnt = 0;
	history.clear();

	DoMove(current_map, 0, result1, history);

	//DescribeState(current_map, 1);

	//bool res = IsStateValid(current_map);

	//res = IsFinished(current_map);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
