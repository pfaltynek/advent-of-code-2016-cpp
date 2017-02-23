#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>

//#define TEST1 1
const int input = 3001330;

int SolvePart2(int count, long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	begin_time = std::chrono::steady_clock::now();
	std::queue<int> thiefs, stolen;
	int tmp;

	begin_time = std::chrono::steady_clock::now();

	for (int i = 0; i < count; i++) {
		if (i < (count / 2)) {
			thiefs.push(i + 1);
		} else {
			stolen.push(i + 1);
		}
	}

	while ((thiefs.size() + stolen.size()) > 1) {
		stolen.pop();
		tmp = thiefs.front();
		thiefs.pop();
		stolen.push(tmp);
		while ((thiefs.size() + 1) < stolen.size()) {
			thiefs.push(stolen.front());
			stolen.pop();
		}
	}


	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return stolen.front();
}

int SolvePart1(int count, long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	begin_time = std::chrono::steady_clock::now();
	std::list<int> circle;
	std::list<int>::iterator pos1, pos2;

	begin_time = std::chrono::steady_clock::now();

	for (int i = 0; i < count; i++) {
		circle.emplace_back(i + 1);
	}

	pos1 = circle.begin();

	while (circle.size() > 1) {
		if (pos1 == circle.end()) {
			pos1 = circle.begin();
		}
		pos2 = pos1;
		pos2++;
		if (pos2 == circle.end()) {
			pos2 = circle.begin();
		}
		circle.erase(pos2);
		pos1++;
	}

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return circle.front();
}

int main(void) {
	int test, result1, result2;
	long ttest, t1, t2;

	std::cout << "=== Advent of Code 2016 - day 19 ====" << std::endl;

#if TEST1
	test = SolvePart1(5, ttest);
	test = SolvePart2(5, ttest);
#endif

	std::cout << "--- part 1 ---" << std::endl;
	result1 = SolvePart1(input, t1);
	std::cout << "Result is " << result1 << " (" << t1 << "ms)" << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	result2 = SolvePart2(input, t2);
	std::cout << "Result is " << result2 << " (" << t2 << "ms)" << std::endl;
}
