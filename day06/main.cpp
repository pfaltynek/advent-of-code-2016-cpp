#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<int, char> char_stat;
typedef std::vector<char_stat> col_stat;

bool StatComparerDesc(char_stat left, char_stat right) {
	if (left.first > right.first) {
		return true;
	}
	if (left.first == right.first) {
		if (left.second < right.second) {
			return true;
		}
	}
	return false;
}

bool StatComparerAsc(char_stat left, char_stat right) {
	if (left.first < right.first) {
		return true;
	}
	if (left.first == right.first) {
		if (left.second > right.second) {
			return true;
		}
	}
	return false;
}


int main(void) {
	std::ifstream input;
	std::string line, result1, result2;
	std::vector<int> triangle, col1, col2, col3;
	std::vector<col_stat> msg_stat;

	std::cout << "=== Advent of Code 2016 - day 6 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	//input.open("input-test.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1.clear();
	result2.clear();
	msg_stat.clear();
	while (std::getline(input, line)) {
		for (int i = msg_stat.size(); i < line.size();
			 i++) { // fill missing column stats
			col_stat col;
			msg_stat.push_back(col);
		}
		for (int i = 0; i < line.size(); i++) {
			char c = line[i];
			bool found = false;
			for (int j = 0; j < msg_stat[i].size(); j++) {
				if (msg_stat[i][j].second == c) {
					msg_stat[i][j].first++;
					found = true;
					break;
				}
			}
			if (!found) {
				char_stat chr;
				chr.first = 1;
				chr.second = c;
				msg_stat[i].push_back(chr);
			}
		}
	}

	for (int i = 0; i < msg_stat.size(); i++) {
		std::sort(msg_stat[i].begin(), msg_stat[i].end(), StatComparerDesc);
		result1 += msg_stat[i][0].second;
		std::sort(msg_stat[i].begin(), msg_stat[i].end(), StatComparerAsc);
		result2 += msg_stat[i][0].second;
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
