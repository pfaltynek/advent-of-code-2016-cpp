#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

bool Decompress(std::string &input, int &part1size, int &part2size, bool &packed_data_found) {
	int pos1, pos2, posx, repeat_len, repeat_cnt;
	int cnt1, cnt2;
	std::string marker, block;
	bool tmp;

	pos1 = input.find('(');
	if (pos1 != std::string::npos) {
		pos2 = input.find(')', pos1);
		if (pos2 == std::string::npos) {
			std::cout << "Invalid marker" << std::endl;
			return false;
		}

		part1size += pos1;
		part2size += pos1;

		marker = input.substr(pos1 + 1, pos2 - pos1 - 1);
		input = input.substr(pos2 + 1);
		posx = marker.find('x');
		if (posx == std::string::npos) {
			std::cout << "Invalid marker" << std::endl;
			return false;
		}
		repeat_len = atoi(marker.substr(0, posx).c_str());
		repeat_cnt = atoi(marker.substr(posx + 1, std::string::npos).c_str());
		block = input.substr(0, repeat_len);
		input = input.substr(repeat_len, std::string::npos);
		part1size += repeat_cnt * repeat_len;
		cnt1 = 0;
		cnt2 = 0;

		do {
			if (!Decompress(block, cnt1, cnt2, tmp)) {
				return false;
			}
		} while (tmp);

		part2size += repeat_cnt * cnt2;

		packed_data_found = true;
	} else {
		part1size += input.size();
		part2size += input.size();
		input.clear();

		packed_data_found = false;
	}

	// no error
	return true;
}

int main(void) {
	std::ifstream input;
	std::string line, packed;
	int result1, result2, position;
	bool packed_data_found;

	std::cout << "=== Advent of Code 2016 - day 9 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	//input.open("input-test.txt", std::ifstream::in);
	//input.open("input-test2.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	position = 0;
	packed.clear();

	while (std::getline(input, line)) {
		packed += line;
		/*
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
				*/
	}

	do {
		if (!Decompress(packed, result1, result2, packed_data_found)) {
			return -1;
		}
	} while (packed_data_found);

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
