
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
//std::regex regex3("[0-9a-f]\\1{2}");
//std::regex regex5("[0-9a-f]\\1{4}");
const std::string salt("cuanljph");
char buff[100];

unsigned int DoIt_part1(long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	unsigned int result = 0, cnt = 0;
	MD5 md5;
	std::string hash;
	std::vector<std::string> list;

	begin_time = std::chrono::steady_clock::now();

	for (int i = 0; i < 50000; i++) {
		sprintf(buff, "%s%d", salt.c_str(), i);
		hash = md5.digestString(buff);
		list.push_back(hash);
	}
	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return result;
}

int main(void) {
	long time = 0, t1 = 0, t2 = 0;
	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;

	std::cout << "--- part 1 ---" << std::endl;
	result1 = DoIt_part1(t1);
	std::cout << "Result is " << result1 << " (" << t1 << "ms)" << std::endl;

	std::cout << "--- part 2 ---" << std::endl;
	//result2 = DoIt_part2(1, 1, 50, 1364, t2);
	std::cout << "Result is " << result2 << " (" << t2 << "ms)" << std::endl;
}
