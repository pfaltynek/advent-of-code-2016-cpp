#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <queue>
#include <unordered_set>

typedef struct {
	int x, y, size, used, avail, use_perc, step_cnt;
} DAY22_NODE;

typedef struct {
	int x,y, step_cnt;
} DAY22_STEP_INFO;

bool DecodeNodeInfo(std::string line, DAY22_NODE &node) {
	std::regex node_info_regex("\\/dev\\/grid\\/node-x(\\d+)-y(\\d+)[[:blank:]]+(\\d+)T[[:blank:]]+(\\d+)T[[:blank:]]+(\\d+)T[[:blank:]]+(\\d+)%$");
	std::smatch sm;

	if (std::regex_match(line, sm, node_info_regex)) {
		node.x = atoi(sm.str(1).c_str());
		node.y = atoi(sm.str(2).c_str());
		node.size = atoi(sm.str(3).c_str());
		node.used = atoi(sm.str(4).c_str());
		node.avail = atoi(sm.str(5).c_str());
		node.use_perc = atoi(sm.str(6).c_str());
		return true;
	}
	return false;
}

int GetViableNodesPairCountBF(std::vector<DAY22_NODE> nodes) {
	int cnt = 0;

	for (int a = 0; a < nodes.size(); a++) {
		for (int b = 0; b < nodes.size(); b++) {
			if (a != b) {
				if (nodes[a].used > 0) {
					if (nodes[a].used <= nodes[b].avail) {
						cnt++;
					}
				}
			}
		}
	}

	return cnt;
}

void PrintMap(std::vector<DAY22_NODE> nodes, int x, int y, int max_avail) {
	std::string line(x + 1, ' ');
	std::vector<std::string> disk_map;

	disk_map.clear();
	for (int i = 0; i <= y; i++) {
		disk_map.push_back(line);
	}

	for (int i = 0; i < nodes.size(); i++) {
		char symbol = '.';

		if ((nodes[i].x == 0) && (nodes[i].y == 0)) {
			symbol = 'S';
		} else if ((nodes[i].x == x) && (nodes[i].y == 0)) {
			symbol = 'T';
		} else if (nodes[i].avail == max_avail) {
			symbol = 'E';
		} else if (nodes[i].used > max_avail) {
			symbol = '#';
		}

		disk_map[nodes[i].y][nodes[i].x] = symbol;
	}

	for (int i = 0; i < disk_map.size(); i++) {
		std::cout << disk_map[i].c_str() << std::endl;
	}
}

int GetCoord(int x, int y) {
	return ((x & 0xFFFF) << 16) | (y & 0xFFFF);
}

void DecodeCoord(int coord, int &x, int &y) {
	x = (coord >> 16) & 0xFFFF;
	y = coord & 0xFFFF;
}

int GetMovementStepsToBringEmptyDiscBeforeTagetData(std::map<int, DAY22_NODE> map, int empty_x, int empty_y, int target_x, int target_y, int max_x, int max_y) {
	int steps = 0, target, coord;
	std::unordered_set<int> history;
	std::queue<DAY22_STEP_INFO> q;
	DAY22_STEP_INFO dsi;

	dsi.x = empty_x;
	dsi.y = empty_y;
	dsi.step_cnt = 0;
	q.push(dsi);

	target = GetCoord(target_x, target_y);

	while (!q.empty()) {
		dsi = q.front();
		q.pop();
		if ((dsi.x < 0) || (dsi.y <0) || (dsi.x > max_x) || (dsi.y > max_y)) {
			continue;
		}
		coord = GetCoord(dsi.x, dsi.y);

		if ((dsi.x == target_x) && (dsi.y == target_y)) {

		}
		dsi.step_cnt++;

	}

	return steps;
}

int GetMovementSteps(std::vector<DAY22_NODE> nodes, int max_x, int max_y, int max_avail_x, int max_avail_y) {
	std::map<int, DAY22_NODE> map;
	int steps = 0;

	map.clear();
	for (int i = 0; i < nodes.size(); i++) {
		map.emplace(GetCoord(nodes[i].x, nodes[i].y), nodes[i]);
	}

	steps += GetMovementStepsToBringEmptyDiscBeforeTagetData(map, max_avail_x, max_avail_y, max_x - 2, 0, max_x, max_y);

	return steps;
}

int main(void) {
	std::ifstream input;
	std::string line;
	std::vector<DAY22_NODE> data;
	int cnt, result1, result2, x, y, max_avail, max_avail_x, max_avail_y;

	cnt = 0;
	result1 = 0;
	result2 = 0;

	std::cout << "=== Advent of Code 2016 - day 22 ====" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	data.clear();
	x = y = max_avail = max_avail_x = max_avail_y = 0;

	while (std::getline(input, line)) {
		DAY22_NODE node;
		cnt++;
		if (DecodeNodeInfo(line, node)) {
			if (node.x > x) {
				x = node.x;
			}
			if (node.y > y) {
				y = node.y;
			}
			if (node.avail > max_avail) {
				max_avail = node.avail;
				max_avail_x = node.x;
				max_avail_y = node.y;
			}
			data.push_back(node);
		} else {
			std::cout << "Line: '" << line << "' ignored." << std::endl;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "--- part 1 ---" << std::endl;
	result1 = GetViableNodesPairCountBF(data);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	//PrintMap(data, x, y, max_avail);	// for manual solving of the part 2
	result2 = GetMovementSteps(data, x + 1, y + 1, max_avail_x, max_avail_y);
	std::cout << "Result is " << result2 << std::endl;
}
