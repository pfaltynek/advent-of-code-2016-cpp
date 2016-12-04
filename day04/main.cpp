#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<int, char> char_stat;

bool StatComparer(char_stat left, char_stat right) {
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

bool IsRoomValid(std::string room, int &sectorID, std::string &decrypted_name) {
	std::vector<char_stat> stat;
	// std::vector<char_stat>::iterator it;
	std::string checksum;
	std::string secID;
	std::string sec_name;
	int pos1, pos2;
	bool found;

	pos1 = room.find('[');
	if (pos1 == std::string::npos) {
		return false;
	} else {
		pos1++;
	}
	pos2 = room.find(']', pos1);
	if (pos2 == std::string::npos) {
		return false;
	}
	checksum = room.substr(pos1, pos2 - pos1);
	if (checksum.size() != 5) {
		return false;
	}
	sec_name = room.substr(0, pos1);
	pos1 = sec_name.find_first_of("0123456789");
	if (pos1 == std::string::npos) {
		return false;
	}
	secID = sec_name.substr(pos1);
	sec_name = sec_name.substr(0, pos1);
	sectorID = atoi(secID.c_str());
	stat.clear();

	for (int i = 0; i < sec_name.size(); i++) {
		if (sec_name[i] != '-') {
			found = false;
			for (int j = 0; j < stat.size(); j++) {
				if (stat[j].second == sec_name[i]) {
					stat[j].first++;
					found = true;
					break;
				}
			}
			if (!found) {
				char_stat y;
				y.first = 1;
				y.second = sec_name[i];
				// stat.push_back(char_stat(1, sec_name[i]));
				stat.push_back(y);
			}
		}
	}

	if (stat.size() < 5) {
		return false;
	}
	std::sort(stat.begin(), stat.end(), StatComparer);

	for (int i = 0; i < 5; i++) {
		if (stat[i].second != checksum[i]) {
			return false;
		}
	}

	decrypted_name = sec_name;

	for (int i = 0; i < decrypted_name.size(); i++) {
		for (int j = 0; j < sectorID; j++) {
			switch (decrypted_name[i]) {
				case 'z':
					decrypted_name[i] = 'a';
					break;
				case 'Z':
					decrypted_name[i] = 'A';
					break;
				case '-':
					decrypted_name[i] = ' ';
					break;
				case ' ':
					break;
				default:
					++decrypted_name[i];
					break;
			}
		}
	}
	return true;
}

int main(void) {
	int cnt, val, result1, result2, sectID;
	std::ifstream input;
	std::string line, decrypted;
	std::vector<int> triangle, col1, col2, col3;

	std::cout << "=== Advent of Code 2016 - day 4 ====" << std::endl;
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
	while (std::getline(input, line)) {
		cnt++;
		if (IsRoomValid(line, sectID, decrypted)) {
			result1 += sectID;
		}
		if (decrypted.find("northpole") == 0) {
			if (result2 == 0) {
				result2 = sectID;
			}
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
