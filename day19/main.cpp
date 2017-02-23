#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include <list>

//#define TEST1 1

int SolvePart1(int count) {
	std::list<int> circle;
	std::list<int>::iterator pos1, pos2;

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

	return circle.front();
}

int main(void) {
	int test, result1, result2;

	int input = 3001330;

	std::cout << "=== Advent of Code 2016 - day 19 ====" << std::endl;

#if TEST1
	test = SolvePart1(5);
#endif

	std::cout << "--- part 1 ---" << std::endl;
	result1 = SolvePart1(input);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	result2 = 0;
	std::cout << "Result is " << result2 << std::endl;
}
