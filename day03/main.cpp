#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool IsTriangle(std::vector<int> triangle) {
	std::vector<int> tmp;
	std::vector<int>::iterator it;

	it = triangle.end();
	tmp.clear();
	tmp.push_back(*(--it));
	tmp.push_back(*(--it));
	tmp.push_back(*(--it));
	std::sort(tmp.begin(), tmp.end());

	return ((tmp[0] + tmp[1]) > tmp[2]);
}

int main(void) {
	int cnt, val, result1, result2;
	std::ifstream input;
	std::string line;
	std::vector<int> triangle, col1, col2, col3;

	std::cout << "=== Advent of Code 2016 - day 3 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	// input.open("input-test.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;
	result1 = 0;
	result2 = 0;
	col1.clear();
	col2.clear();
	col3.clear();
	while (std::getline(input, line)) {
		cnt++;
		triangle.clear();
		std::stringstream stream(line);
		while (stream >> val) {
			triangle.push_back(val);
		}
		if (triangle.size() != 3) {
			std::cout << "Invalid tiangle definition at line " << cnt
					  << std::endl;
			return -1;
		}
		if (IsTriangle(triangle)) {
			result1++;
		}
		col1.push_back(triangle[0]);
		col2.push_back(triangle[1]);
		col3.push_back(triangle[2]);
		if (col1.size() >= 3) {
			if (IsTriangle(col1)) {
				result2++;
			}
			if (IsTriangle(col2)) {
				result2++;
			}
			if (IsTriangle(col3)) {
				result2++;
			}
			col1.clear();
			col2.clear();
			col3.clear();
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
