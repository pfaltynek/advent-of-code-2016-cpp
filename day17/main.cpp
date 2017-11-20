
#include "md5.h"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

std::string result1, test1, tmp;
int result2, test2;

#define TEST1 0
#define TEST2 0

#define GO_UP 1
#define GO_DOWN 2
#define GO_LEFT 4
#define GO_RIGHT 8

char buffer[1000001];
const std::string salt = "rrrbmfta";

bool IsOpened(char wall_value) {
	return (((wall_value >= 'B') && (wall_value <= 'F')) || ((wall_value >= 'b') && (wall_value <= 'f')));
}

int GetUnlockedDirections(std::string md5_salt, std::string path) {
	std::string hash;
	int i, result;
	char x;
	MD5 md5;

	sprintf(buffer, "%s%s", md5_salt.c_str(), path.c_str());
	hash = md5.digestString(buffer);
	result = 0;
	i = 0;

	if (IsOpened(hash[0])) {
		result |= GO_UP;
	}
	if (IsOpened(hash[1])) {
		result |= GO_DOWN;
	}
	if (IsOpened(hash[2])) {
		result |= GO_LEFT;
	}
	if (IsOpened(hash[3])) {
		result |= GO_RIGHT;
	}

	return result;
}

void ExplorePath1(std::string salt, std::string path, int x, int y, std::string &result) {
	std::string new_path;
	int state;

	if ((x == 3) && (y == 3)) {
		result = path;
		return;
	}

	if (!result.empty()) {
		if ((path.size() + 1) >= result.size()) {
			return;
		}
	}

	state = GetUnlockedDirections(salt, path);

	if ((state & GO_DOWN) && (y < 3)) {
		new_path = path;
		new_path += 'D';
		ExplorePath1(salt, new_path, x, y + 1, result);
	}
	if ((state & GO_RIGHT) && (x < 3)) {
		new_path = path;
		new_path += 'R';
		ExplorePath1(salt, new_path, x + 1, y, result);
	}
	if ((state & GO_UP) && (y > 0)) {
		new_path = path;
		new_path += 'U';
		ExplorePath1(salt, new_path, x, y - 1, result);
	}
	if ((state & GO_LEFT) && (x > 0)) {
		new_path = path;
		new_path += 'L';
		ExplorePath1(salt, new_path, x - 1, y, result);
	}
}

void ExplorePath2(std::string salt, std::string path, int x, int y, int &result) {
	int state;

	if ((x == 3) && (y == 3)) {
		if (result < path.size()) {
			result = path.size();
		}
		return;
	}

	state = GetUnlockedDirections(salt, path);

	if ((state & GO_DOWN) && (y < 3)) {
		path.push_back('D');
		ExplorePath2(salt, path, x, y + 1, result);
		path.pop_back();
	}
	if ((state & GO_RIGHT) && (x < 3)) {
		path.push_back('R');
		ExplorePath2(salt, path, x + 1, y, result);
		path.pop_back();
	}
	if ((state & GO_UP) && (y > 0)) {
		path.push_back('U');
		ExplorePath2(salt, path, x, y - 1, result);
		path.pop_back();
	}
	if ((state & GO_LEFT) && (x > 0)) {
		path.push_back('L');
		ExplorePath2(salt, path, x - 1, y, result);
		path.pop_back();
	}
}

void ExploreMaze1(std::string hash_salt, std::string &result, long &time_msec) {
	int x, y;
	std::chrono::steady_clock::time_point begin_time, end_time;
	std::string path;
	begin_time = std::chrono::steady_clock::now();

	x = 0;
	y = 0;
	path = "";
	result = "";

	ExplorePath1(hash_salt, path, x, y, result);

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
}

void ExploreMaze2(std::string hash_salt, int &result, long &time_msec) {
	int x, y;
	std::chrono::steady_clock::time_point begin_time, end_time;
	std::string path;
	begin_time = std::chrono::steady_clock::now();

	x = 0;
	y = 0;
	path = "";

	ExplorePath2(hash_salt, path, x, y, result);

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();
}

int main(void) {
	long time = 0, t1 = 0, t2 = 0;
	std::cout << "=== Advent of Code 2016 - day 17 ====" << std::endl;

#if TEST1
	std::cout << "--- test ---" << std::endl;
	tmp = "ihgpwlah";
	ExploreMaze1(tmp, test1, time);
	std::cout << "Result of test for '" << tmp.c_str() << "' is " << test1.c_str() << " (" << time << "ms)" << std::endl;

	tmp = "kglvqrro";
	ExploreMaze1(tmp, test1, time);
	std::cout << "Result of test for '" << tmp.c_str() << "' is " << test1.c_str() << " (" << time << "ms)" << std::endl;

	tmp = "ulqzkmiv";
	ExploreMaze1(tmp, test1, time);

	std::cout << "Result of test for '" << tmp.c_str() << "' is " << test1.c_str() << " (" << time << "ms)" << std::endl;
#endif

#if TEST2
	std::cout << "--- test ---" << std::endl;
	tmp = "ihgpwlah";
	ExploreMaze2(tmp, test2, time);
	std::cout << "Result of test for '" << tmp.c_str() << "' is " << test2 << " (" << time << "ms)" << std::endl;

	tmp = "kglvqrro";
	ExploreMaze2(tmp, test2, time);
	std::cout << "Result of test for '" << tmp.c_str() << "' is " << test2 << " (" << time << "ms)" << std::endl;

	tmp = "ulqzkmiv";
	ExploreMaze2(tmp, test2, time);

	std::cout << "Result of test for '" << tmp.c_str() << "' is " << test2 << " (" << time << "ms)" << std::endl;
#endif

	std::cout << "--- part 1 ---" << std::endl;
	ExploreMaze1(salt, result1, t1);
	std::cout << "Result is " << result1.c_str() << " (" << t1 << "ms)" << std::endl;

	std::cout << "--- part 2 ---" << std::endl;
	ExploreMaze2(salt, result2, t2);
	std::cout << "Result is " << result2 << " (" << t2 << "ms)" << std::endl;
}
