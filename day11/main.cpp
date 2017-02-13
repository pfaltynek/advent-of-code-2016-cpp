
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

#include <queue>

#define FIRST_FLOOR 0
#define FINAL_FLOOR 3

#define GENERATOR 0
#define MICROCHIP 1
const std::string type_names[] = {"G", "M"};
const std::string empty_type_name = ".";
const std::string empty_name = ".";

#define MAX_RTG_TYPES 7
#define MAX_RTG_TYPES_TEST 2
#define MAX_RTG_TYPES_PART1 5
#define MAX_RTG_TYPES_PART2 7
const int init_map_test[MAX_RTG_TYPES_TEST][2] = {{FIRST_FLOOR + 1, FIRST_FLOOR}, {FIRST_FLOOR + 2, FIRST_FLOOR}};
const int init_map_part1[MAX_RTG_TYPES_PART1][2] = {{FIRST_FLOOR, FIRST_FLOOR}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}};
const int init_map_part2[MAX_RTG_TYPES_PART2][2] = {{FIRST_FLOOR, FIRST_FLOOR}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR + 1, FIRST_FLOOR + 2}, {FIRST_FLOOR, FIRST_FLOOR}, {FIRST_FLOOR, FIRST_FLOOR}};

typedef struct {
	int Gen;
	int Chip;
} RTG_PAIR;

typedef struct {
	RTG_PAIR map[MAX_RTG_TYPES];
	int elevator;
	int step_no;
} HOUSE_MAP;

int result1, result2;
int real_rtg_types_count = MAX_RTG_TYPES_TEST;

#define TEST 1

void DescribeState(const HOUSE_MAP current_map) {
	std::cout << std::endl;
	for (int i = FINAL_FLOOR; i >= FIRST_FLOOR; i--) {
		std::cout << 'F' << i << ' ';
		if (current_map.elevator == i) {
			std::cout << "E ";
		} else {
			std::cout << ". ";
		}
		for (int j = 0; j < real_rtg_types_count; j++) {
			if (current_map.map[j].Gen == i) {
				std::cout << (char)('A' + j) << type_names[GENERATOR].c_str();
			} else {
				std::cout << empty_name.c_str() << empty_type_name.c_str();
			}

			std::cout << ' ';

			if (current_map.map[j].Chip == i) {
				std::cout << (char)('A' + j) << type_names[MICROCHIP].c_str();
			} else {
				std::cout << empty_name.c_str() << empty_type_name.c_str();
			}

			std::cout << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

unsigned long long PackState(HOUSE_MAP state) {
	unsigned long long result = 0;
	unsigned char packed[MAX_RTG_TYPES];

	// pack state
	for (int i = 0; i < real_rtg_types_count; i++) {
		packed[i] = (state.map[i].Gen & 0x0F);
		packed[i] = packed[i] << 4;
		packed[i] |= (state.map[i].Chip & 0x0F);
	}

	// order packed items
	for (int i = 0; i < (real_rtg_types_count - 1); i++) {
		if (packed[i] > packed[i + 1]) {
			unsigned char tmp = packed[i];
			packed[i] = packed[i + 1];
			packed[i + 1] = tmp;
		}
	}

	// pack all into one value
	result = state.elevator;
	for (int i = 0; i < real_rtg_types_count; i++) {
		result = result << 8;
		result |= packed[i];
	}

	return result;
}

bool IsStateValid(const HOUSE_MAP current_map) {
	bool is_gen, is_unpaired_chip;

	for (int i = FIRST_FLOOR; i <= FINAL_FLOOR; i++) {
		is_gen = is_unpaired_chip = false;

		for (int j = 0; j < real_rtg_types_count; j++) {
			if (current_map.map[j].Gen == i) {
				is_gen = true;
			}
			if ((current_map.map[j].Chip == i) && (current_map.map[j].Gen != i)) {
				is_unpaired_chip = true;
			}
		}
		if (is_gen && is_unpaired_chip) {
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

void MoveItem(HOUSE_MAP &next_map, int rtg_item_type, int item_type, int new_floor) {
	if (item_type == GENERATOR) {
		next_map.map[rtg_item_type].Gen = new_floor;
	} else {
		next_map.map[rtg_item_type].Chip = new_floor;
	}
}

bool IsInHistory(unsigned long long stamp, std::vector<unsigned long long> history) {
	//return (std::find(history.begin(), history.end(), stamp) != history.end());
	if (std::find(history.begin(), history.end(), stamp) != history.end()) {
		return true;
	} else {
		return false;
	}
}

int Explore2(HOUSE_MAP init_map) {
	std::vector<unsigned long long> history;
	HOUSE_MAP current_map, next, next2;
	unsigned long long stamp, target;
	int curr_floor_map[MAX_RTG_TYPES * 2][2];
	int curr_floor_map_size;
	std::queue<HOUSE_MAP> queue;

	current_map.elevator = FINAL_FLOOR;
	for (int j = 0; j < real_rtg_types_count; j++) {
		current_map.map[j].Gen = FINAL_FLOOR;
		current_map.map[j].Chip = FINAL_FLOOR;
	}
	target = PackState(current_map);

	history.clear();
	//queue.clear();
	queue.push(init_map);

	while (queue.size() > 0) {
		current_map = queue.front();
		queue.pop();
		stamp = PackState(current_map);

		if (stamp == target) {
			return current_map.step_no;
		}

		if (IsInHistory(stamp, history)) {
			continue;
		} else {
			history.push_back(stamp);
		}

		current_map.step_no++;

		curr_floor_map_size = 0;
		for (int j = 0; j < real_rtg_types_count; j++) {
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
				next = current_map;
				next.elevator--;
				MoveItem(next, curr_floor_map[i][0], curr_floor_map[i][1], next.elevator);
				if (IsStateValid(next)) {
					queue.push(next);
				}
				for (int j = i + 1; j < curr_floor_map_size; j++) {
					next2 = next;
					MoveItem(next2, curr_floor_map[j][0], curr_floor_map[j][1], next2.elevator);
					if (IsStateValid(next2)) {
						queue.push(next2);
					}
				}
			}
			if (current_map.elevator < FINAL_FLOOR) {
				next = current_map;
				next.elevator++;
				MoveItem(next, curr_floor_map[i][0], curr_floor_map[i][1], next.elevator);
				if (IsStateValid(next)) {
					queue.push(next);
				}
				for (int j = i + 1; j < curr_floor_map_size; j++) {
					next2 = next;
					MoveItem(next2, curr_floor_map[j][0], curr_floor_map[j][1], next2.elevator);
					if (IsStateValid(next2)) {
						queue.push(next2);
					}
				}
			}
		}
	}

	return -1;
}

int main(void) {
	HOUSE_MAP current_map;
	std::vector<unsigned long long> optim;

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;

#if TEST
	std::cout << "--- test ---" << std::endl;

	real_rtg_types_count = MAX_RTG_TYPES_TEST; //MAX_RTG_TYPES_PART1;
	for (int j = 0; j < real_rtg_types_count; j++) {
		current_map.map[j].Gen = init_map_test[j][GENERATOR];
		current_map.map[j].Chip = init_map_test[j][MICROCHIP];
	}
	current_map.elevator = FIRST_FLOOR;
	current_map.step_no = 0;
	optim.clear();
	//DescribeState(current_map);

	result1 = Explore2(current_map);
#endif

	std::cout << "--- part 1 ---" << std::endl;

	real_rtg_types_count = MAX_RTG_TYPES_PART1;
	for (int j = 0; j < real_rtg_types_count; j++) {
		current_map.map[j].Gen = init_map_part1[j][GENERATOR];
		current_map.map[j].Chip = init_map_part1[j][MICROCHIP];
	}
	current_map.elevator = FIRST_FLOOR;
	current_map.step_no = 0;
	optim.clear();
	//DescribeState(current_map);
	result1 = Explore2(current_map);

	real_rtg_types_count = MAX_RTG_TYPES_PART2;
	for (int j = 0; j < real_rtg_types_count; j++) {
		current_map.map[j].Gen = init_map_part2[j][GENERATOR];
		current_map.map[j].Chip = init_map_part2[j][MICROCHIP];
	}
	current_map.elevator = FIRST_FLOOR;
	current_map.step_no = 0;
	optim.clear();
	//DescribeState(current_map);
	//result2 = Explore2(current_map);

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
