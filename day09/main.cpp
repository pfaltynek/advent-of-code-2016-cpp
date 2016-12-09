#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, result2, cnt, repeat_len, repeat_cnt;
	std::string output, marker, repeat_part;

	std::cout << "=== Advent of Code 2016 - day 9 ====" << std::endl;
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
	output.clear();

	while (std::getline(input, line)) {
		std::string block;
		int pos1, pos2, posx;

		cnt++;
		pos1 = line.find('(');
		while (pos1 != std::string::npos) {
			pos2 = line.find(')', pos1);
			if (pos2 == std::string::npos) {
				std::cout << "Invalid marker at line " << cnt << std::endl;
				return -1;
			}
			output += line.substr(0, pos1);
			marker = line.substr(pos1 + 1, pos2 - pos1 - 1);
			line = line.substr(pos2 + 1);
			posx = marker.find('x');
			if (posx == std::string::npos) {
				std::cout << "Invalid marker at line " << cnt << std::endl;
				return -1;
			}
			repeat_len = atoi(marker.substr(0, posx).c_str());
			repeat_cnt =
				atoi(marker.substr(posx + 1, std::string::npos).c_str());
			block = line.substr(0, repeat_len);
			line = line.substr(repeat_len, std::string::npos);
			for (int i = 0; i < repeat_cnt; i++) {
				output += block;
			}
			pos1 = line.find('(');
		}

		output += line;
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = output.size();

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;

	std::cout << output;
}
