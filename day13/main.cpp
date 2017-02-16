
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define TEST 1

int result1, result2, test;

class FuncCall {
  public:
	unsigned int x, y, step;
	int k;
	int e;
	FuncCall(unsigned int x, unsigned int y, unsigned int step) {
		this->x = x;
		this->y = y;
		this->step = step;
	}
};

/*bool ComparePairs(Pair p1, Pair p2) {
	if (p1.x != p2.x) {
		return p1.x < p2.x;
	}
	return p1.y < p2.y;
}*/

bool IsEvenParity(unsigned int v) {
	v ^= v >> 1;
	v ^= v >> 2;
	v = (v & 0x11111111U) * 0x11111111U;
	return ((v >> 28) & 1) != 1;
}

bool IsSpace(unsigned int x, unsigned int y, unsigned int number) {
	return IsEvenParity((x * x) + (3 * x) + (2 * x * y) + y + (y * y) + number);
}

unsigned int GetCoord(unsigned int x, unsigned int y) {
	return (1000 * x) + y;
}

unsigned int DoIt_part1(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int magic, long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	unsigned int result = 0;
	std::unordered_map<unsigned int, bool> map;
	unsigned int target, coord;
	std::queue<FuncCall> bfs;
	bool space;

	begin_time = std::chrono::steady_clock::now();

	target = GetCoord(x2, y2);
	FuncCall funccall(1, 1, 0);
	bfs.push(funccall);
	while (!bfs.empty()) {
		FuncCall f = bfs.front();
		bfs.pop();

		coord = GetCoord(f.x, f.y);

		if (coord == target) {
			result = f.step;
			break;
		}

		if (map.find(coord) != map.end())
			continue;

		space = IsSpace(f.x, f.y, magic);
		map.emplace(coord, space);
		if (space) {
			if (f.x) {
				bfs.push(FuncCall(f.x - 1, f.y, f.step + 1));
			}
			if (f.y) {
				bfs.push(FuncCall(f.x, f.y - 1, f.step + 1));
			}
			bfs.push(FuncCall(f.x + 1, f.y, f.step + 1));
			bfs.push(FuncCall(f.x, f.y + 1, f.step + 1));
		}
	}

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return result;
}

unsigned int DoIt_part2(unsigned int x1, unsigned int y1, unsigned int steps_max, unsigned int magic, long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	unsigned int result = 0;
	std::unordered_set<unsigned int> map;
	unsigned int coord;
	std::queue<FuncCall> bfs;
	bool space;

	begin_time = std::chrono::steady_clock::now();

	FuncCall funccall(1, 1, 0);
	bfs.push(funccall);
	while (!bfs.empty()) {
		FuncCall f = bfs.front();
		bfs.pop();

		coord = GetCoord(f.x, f.y);

		if (f.step > steps_max) {
			break;
		}

		if (map.find(coord) != map.end())
			continue;

		space = IsSpace(f.x, f.y, magic);
		if (space)
			result++;

		map.emplace(coord);
		if (space) {
			if (f.x) {
				bfs.push(FuncCall(f.x - 1, f.y, f.step + 1));
			}
			if (f.y) {
				bfs.push(FuncCall(f.x, f.y - 1, f.step + 1));
			}
			bfs.push(FuncCall(f.x + 1, f.y, f.step + 1));
			bfs.push(FuncCall(f.x, f.y + 1, f.step + 1));
		}
	}

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return result;
}

int main(void) {
	long time = 0, t1 = 0, t2 = 0;
	std::cout << "=== Advent of Code 2016 - day 13 ====" << std::endl;

#if TEST
	std::cout << "--- test ---" << std::endl;
	test = DoIt_part1(1, 1, 7, 4, 10, time);
	std::cout << "Result is " << test << " (" << time << "ms)" << std::endl;
#endif

	std::cout << "--- part 1 ---" << std::endl;
	result1 = DoIt_part1(1, 1, 31, 39, 1364, t1);
	std::cout << "Result is " << result1 << " (" << t1 << "ms)" << std::endl;

	std::cout << "--- part 2 ---" << std::endl;
	result2 = DoIt_part2(1, 1, 50, 1364, t2);
	std::cout << "Result is " << result2 << " (" << t2 << "ms)" << std::endl;
}
