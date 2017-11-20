#include "md5.h"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int result1, result2, test;
std::regex regex3("([0-9a-f])\\1{2}");
std::regex regex5("([0-9a-f])\\1{4}");
const std::string salt("cuanljph");

class KeyInfo {
  public:
	unsigned int size, index;
	char character;
	KeyInfo(unsigned int size, unsigned int index, char character) {
		this->size = size;
		this->index = index;
		this->character = character;
	}
};

KeyInfo GetNextPossibleKeyInfo(std::string salt4hash, unsigned int repeats, unsigned int &index) {
	char buff[100];
	std::smatch sm;
	std::string hash;
	MD5 md5;
	char chr;

	do {
		sprintf(buff, "%s%d", salt4hash.c_str(), index);
		hash = md5.digestString(buff);
		for (int i = 0; i < repeats; i++) {
			strcpy(buff, hash.c_str());
			hash = md5.digestString(buff);
		}
		index++;
	} while (!regex_search(hash, sm, regex3));

	chr = sm[0].str()[0];
	if (regex_search(hash, sm, regex5)) {
		return KeyInfo(5, index - 1, chr);
	} else {
		return KeyInfo(3, index - 1, chr);
	}
}

unsigned int DoIt(std::string salt4hash, unsigned int repeats, long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	unsigned int index = 0, cnt = 0, result = 0, start = 0;
	std::string hash;
	std::vector<KeyInfo> list;

	begin_time = std::chrono::steady_clock::now();

	do {

		KeyInfo ki = GetNextPossibleKeyInfo(salt4hash, repeats, index);
		list.push_back(ki);

		if (ki.size == 5) {
			cnt = 0;
			for (unsigned int i = 0; i < list.size(); i++) {
				for (unsigned int j = i + 1; j < list.size(); j++) {
					if ((list[i].character == list[j].character) && (list[j].size == 5) && ((list[i].index + 1000) >= list[j].index)) {
						result = list[i].index;
						cnt++;
						break;
					}
				}
				if (cnt == 64) {
					break;
				}
			}
		}
	} while (cnt < 64);

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return result;
}

int main(void) {
	long time = 0, t1 = 0, t2 = 0;
	std::cout << "=== Advent of Code 2016 - day 14 ====" << std::endl;

	std::cout << "--- part 1 ---" << std::endl;

	result1 = DoIt(salt, 0, t1);
	std::cout << "Result is " << result1 << " (" << t1 << "ms)" << std::endl;

	std::cout << "--- part 2 ---" << std::endl;
	
	result2 = DoIt(salt, 2016, t2);
	std::cout << "Result is " << result2 << " (" << t2 << "ms)" << std::endl;
}
