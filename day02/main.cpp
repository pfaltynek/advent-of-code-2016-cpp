#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const char keypad1[3][3] = {{'1', '4', '7'}, {'2', '5', '8'}, {'3', '6', '9'}};
const char keypad2[5][5] = {{0, 0, '5', 0, 0},
							{0, '2', '6', 'A', 0},
							{'1', '3', '7', 'B', 'D'},
							{0, '4', '8', 'C', 0},
							{0, 0, '9', 0, 0}};

int main(void) {
	int cnt, x1, x2, y1, y2;
	std::ifstream input;
	std::string line, result1, result2;

	std::cout << "=== Advent of Code 2016 - day 2 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	//input.open("input-test.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;
	result1.clear();
	result2.clear();
	x1 = 1;
	y1 = 1;
	x2 = 0;
	y2 = 2;
	while (std::getline(input, line)) {
		cnt++;
		for (int i = 0; i < line.size(); i++) {
			switch (line[i]) {
				case 'd':
				case 'D':
					if (y1 < 2) {
						y1++;
					}
					if (y2 < 5) {
						if (keypad2[x2][y2 + 1]) {
							y2++;
						}
					}
					break;
				case 'u':
				case 'U':
					if (y1 > 0) {
						y1--;
					}
					if (y2 > 0) {
						if (keypad2[x2][y2 - 1]) {
							y2--;
						}
					}
					break;
				case 'l':
				case 'L':
					if (x1 > 0) {
						x1--;
					}
					if (x2 > 0) {
						if (keypad2[x2 - 1][y2]) {
							x2--;
						}
					}
					break;
				case 'r':
				case 'R':
					if (x1 < 2) {
						x1++;
					}
					if (x2 < 5) {
						if (keypad2[x2 + 1][y2]) {
							x2++;
						}
					}
					break;
				case '\r':
				case '\n':
					break;
				default:
					std::cout << "Invalid instruction character at line " << cnt
							  << ", position " << i << std::endl;
					return -1;
			}
		}
		result1 += keypad1[x1][y1];
		result2 += keypad2[x2][y2];
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
