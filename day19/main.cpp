#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define TEST1 1

int SolvePart1(int count) {
	std::vector<int> circle(count,0);
	int x = 0;

	for (int i = 0; i < count; i++) {
		circle[i] = i + 1;
	}
	
	while (circle.size() > 1) {
		x++;
		if (x >= circle.size()) {
			x = 0;
		}
		circle.erase(circle.begin() + x);
	}
	
	return circle[0];
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
	std::cout << "Result is:" << result2 << std::endl;
}
