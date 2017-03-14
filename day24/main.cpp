#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include <unordered_set>

typedef struct {
	int x, y, step_cnt;
} MAZE_POS;

int GetCoord(int x, int y) {
	//return ((x & 0xFFFF) << 16) | (y & 0xFFFF);
	return (x * 1000) + y;
}

void DecodeCoord(int coord, int &x, int &y) {
	x = coord / 1000;
	y = coord % 1000;
}

int FindShortestWayStepCount(std::map<int, char> map, int from_x, int from_y, int to_x, int to_y, int max_x, int max_y, std::vector<char> &also_visited) {
	int target, coord;
	std::unordered_set<int> history;
	std::queue<MAZE_POS> q;
	MAZE_POS position, tmp;

	position.x = from_x;
	position.y = from_y;
	position.step_cnt = 0;
	q.push(position);

	target = GetCoord(to_x, to_y);

	while (!q.empty()) {
		position = q.front();
		q.pop();
		if ((position.x < 0) || (position.y < 0) || (position.x > max_x) || (position.y > max_y)) {
			continue;
		}

		coord = GetCoord(position.x, position.y);

		if (coord == target) {
			return position.step_cnt;
		}

		if (history.find(coord) != history.end()) {
			continue;
		}

		history.emplace(coord);

		switch (map[coord]) {
			case '.':
				break;

			case '#':
				continue;
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (std::find(also_visited.begin(), also_visited.end(), map[coord]) == also_visited.end()) {
					also_visited.push_back(map[coord]);
				}
				break;

			default:
				int j = 159;
				break;
		}

		position.step_cnt++;
		tmp = position;
		position.x++;
		q.push(position);
		position = tmp;
		position.x--;
		q.push(position);
		position = tmp;
		position.y++;
		q.push(position);
		position = tmp;
		position.y--;
		q.push(position);
	}

	return -1;
}

void GoThroughCheckPoints(std::map<int, char> map, std::map<char, int> check_points, int from_x, int from_y, int max_x, int max_y, int &steps_cnt, std::vector<char> checkpoints_to_visit) {
	int to_x, to_y;

	for (int i = 0; i < checkpoints_to_visit.size(); i++) {
		std::vector<char> visited;
		visited.clear();
		DecodeCoord(check_points[checkpoints_to_visit[i]], to_x, to_y);
		FindShortestWayStepCount(map, from_x, from_y, to_x, to_y, max_x, max_y, visited);
	}
}

int GetMovementSteps(std::map<int, char> map, std::map<char, int> check_points, int max_x, int max_y, char start_chr) {
	std::vector<char> to_visit;
	std::map<char, int>::iterator it;
	int x1, y1, steps;

	if (check_points.find(start_chr) == check_points.end()) {
		return -1;
	} else {
		DecodeCoord(check_points[start_chr], x1, y1);
		check_points.erase(start_chr);
	}

	for (it = check_points.begin(); it != check_points.end(); ++it) {
		to_visit.push_back(it->first);
	}

	steps = 0x7FFFFFFF;

	GoThroughCheckPoints(map, check_points, x1, y1,max_x, max_y, steps, to_visit);

	return steps;
}

/*
int GetMovementSteps(std::vector<DAY22_NODE> nodes, int max_x, int max_y, int max_avail_x, int max_avail_y) {
	std::map<int, DAY22_NODE> map;
	int steps = 0, available;
	int xa, ya, xd, yd, tmp;

	map.clear();
	for (int i = 0; i < nodes.size(); i++) {
		map.emplace(GetCoord(nodes[i].x, nodes[i].y), nodes[i]);
	}

	available = map[GetCoord(max_avail_x, max_avail_y)].avail;

	xa = max_avail_x;
	ya = max_avail_y;
	xd = max_x;
	yd = 0;

	steps += FindShortestWayStepCount(map, xa, ya, xd - 1, yd, max_x, max_y, available, std::vector<int>());

	xa = xd - 1;
	ya = yd;

	if ((yd == ya) && (xd == xa + 1)) {
		xd--;
		xa++;
		steps++;
	}

	while ((xd != 0) || (yd != 0)) {
		if ((yd == ya) && (xa == xd + 1)) {
			std::vector<int> tabu;
			tabu.push_back(GetCoord(xd, yd));
			steps += FindShortestWayStepCount(map, xa, ya, xd - 1, yd, max_x, max_y, available, tabu);
			xa = xd - 1;
		} else {
			int z = 13;
		}
		if ((yd == ya) && (xd == xa + 1)) {
			xd--;
			xa++;
			steps++;
		} else {
			int z = 13;
		}
	}

	return steps;
}
*/
int main(void) {
	std::ifstream input;
	std::string line;
	std::map<int, char> data;
	std::map<char, int> check_points;
	int cnt, result1, result2, line_len, coord;

	cnt = 0;
	result1 = 0;
	result2 = 0;
	line_len = -1;

	std::cout << "=== Advent of Code 2016 - day 24 ====" << std::endl;

#if TEST
	input.open("input-test.txt", std::ifstream::in);
#else
	input.open("input.txt", std::ifstream::in);
#endif

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	data.clear();
	check_points.clear();

	while (std::getline(input, line)) {
		if (line_len < 0) {
			line_len = line.size();
		} else {
			if (line_len != line.size()) {
				std::cout << "Invalid length of line " << cnt + 1 << "." << std::endl;
				return -1;
			}
		}
		for (int i = 0; i < line.size(); i++) {
			coord = GetCoord(i, cnt);
			data[coord] = line[i];
			if ((line[i] >= '0') && (line[i] <= '9')) {
				check_points[line[i]] = coord;
			}
		}
		cnt++;
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "--- part 1 ---" << std::endl;

	result1 = GetMovementSteps(data, check_points, line_len - 1, cnt - 1, '0');
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	std::cout << "Result is " << result2 << std::endl;
}
