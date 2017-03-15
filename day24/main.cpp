#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <string>
#include <unordered_set>

//#define TEST 1

typedef struct {
	int x, y, step_cnt;
	std::vector<char> visited;
} MAZE_POS;

std::map<int, char> map;
std::map<char, int> check_points;
int max_x, max_y;
std::map<std::string, MAZE_POS> cache;

int GetCoord(int x, int y) {
	//return ((x & 0xFFFF) << 16) | (y & 0xFFFF);
	return (x * 1000) + y;
}

void DecodeCoord(int coord, int &x, int &y) {
	x = coord / 1000;
	y = coord % 1000;
}

int FindShortestWayStepCount(char start, char finish, std::vector<char> &also_visited) {
	int target, coord;
	int to_x, to_y;
	std::unordered_set<int> history;
	std::queue<MAZE_POS> q;
	std::string path;
	MAZE_POS position, tmp;

	path = start;
	path += finish;

	if (cache.find(path) != cache.end()) {
		also_visited = cache[path].visited;
		return cache[path].step_cnt;
	}

	DecodeCoord(check_points[start], position.x, position.y);
	position.step_cnt = 0;
	position.visited.clear();
	q.push(position);

	target = check_points[finish];

	while (!q.empty()) {
		position = q.front();
		q.pop();
		if ((position.x < 0) || (position.y < 0) || (position.x > max_x) || (position.y > max_y)) {
			continue;
		}

		coord = GetCoord(position.x, position.y);

		if (coord == target) {
			cache[path] = position;
			also_visited = position.visited;
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
				position.visited.push_back(map[coord]);
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

void GoThroughCheckPoints(char start_from, int steps_cnt, int &result1, int &result2, std::vector<char> checkpoints_to_visit) {
	int to_x, to_y, steps, steps2;
	char finish;

	for (int i = 0; i < checkpoints_to_visit.size(); i++) {
		std::vector<char> visited, new2visit(checkpoints_to_visit);
		std::vector<char>::iterator it;

		steps = steps_cnt;
		visited.clear();
		steps += FindShortestWayStepCount(start_from, checkpoints_to_visit[i], visited);
		it = std::find(new2visit.begin(), new2visit.end(), checkpoints_to_visit[i]);
		if (it != new2visit.end()) {
			new2visit.erase(it);
		}

		for (int j = 0; j < visited.size(); j++) {
			it = std::find(new2visit.begin(), new2visit.end(), visited[j]);
			if (it != new2visit.end()) {
				new2visit.erase(it);
			}
		}
		if (new2visit.size()) {
			GoThroughCheckPoints(checkpoints_to_visit[i], steps, result1, result2, new2visit);
		} else {
			if (steps < result1) {
				result1 = steps;
			}
			steps2 = steps;
			visited.clear();
			steps2 += FindShortestWayStepCount('0', checkpoints_to_visit[i], visited);
			if (steps2 < result2) {
				result2 = steps2;
			}
		}
	}
}

void GetMovementSteps(char start_chr, int &result1, int &result2) {
	std::vector<char> to_visit;
	std::map<char, int>::iterator it;
	int x1, y1;

	result1 = -1;
	result2 = -1;

	if (check_points.find(start_chr) == check_points.end()) {
		return;
	}

	for (it = check_points.begin(); it != check_points.end(); ++it) {
		if (it->first != start_chr) {
			to_visit.push_back(it->first);
		}
	}

	result1 = 0x7FFFFFFF;
	result2 = 0x7FFFFFFF;

	GoThroughCheckPoints(start_chr, 0, result1, result2, to_visit);
}

int main(void) {
	std::ifstream input;
	std::string line;
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

	map.clear();
	check_points.clear();
	cache.clear();

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
			map[coord] = line[i];
			if ((line[i] >= '0') && (line[i] <= '9')) {
				check_points[line[i]] = coord;
			}
		}
		cnt++;
	}

	max_x = line_len - 1;
	max_y = cnt - 1;

	if (input.is_open()) {
		input.close();
	}

	std::cout << "--- part 1 ---" << std::endl;

	GetMovementSteps('0', result1, result2);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	std::cout << "Result is " << result2 << std::endl;
}
