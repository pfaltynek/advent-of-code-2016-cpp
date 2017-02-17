
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#include "md5.h"

#define FIRST_FLOOR 0
#define FINAL_FLOOR 3

#define GENERATOR 0
#define MICROCHIP 1
int result1, result2, test;

#define TEST 1
#define STRING_HISTORY 0

const std::string salt = "rrrbmfta";

class FuncCall {
  public:
	std::vector<int> n;
	int k;
	int e;
	FuncCall(std::vector<int> n, int k, int e) {
		this->n = std::vector<int>(n);
		this->e = e;
		this->k = k;
	}
};

class Pair {
  public:
	int x, y;
	Pair(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

bool ComparePairs(Pair p1, Pair p2) {
	if (p1.x != p2.x) {
		return p1.x < p2.x;
	}
	return p1.y < p2.y;
}

static void sortx(std::vector<int> n) {
	std::vector<Pair> pairs;

	for (int i = 0; i < (n.size() / 2); i++) {
		Pair p(n[2 * i], n[2 * i + 1]);
		pairs.push_back(p);
	}
	std::sort(pairs.begin(), pairs.end(), ComparePairs);
	for (int i = 0; i < pairs.size(); i++) {
		n[2 * i] = pairs[i].x;
		n[2 * i + 1] = pairs[i].y;
	}
}

bool ok(std::vector<int> n) {
	for (int i = 0; i < n.size(); i += 2) //microships
		if (n[i] != n[i + 1])
			for (int j = 1; j < n.size(); j += 2) //generator
				if (n[j] == n[i])				  //microship getting fried.
					return false;
	return true;
}

#if STRING_HISTORY
std::string getStr(std::vector<int> n, int e) {
	std::string result;

	result.clear();
	result += (char)(e + '0');

	for (int i = 0; i < n.size(); i++) {
		result += (char)(n[i] + '0');
	}

	return result;
}
#else
uint32_t GetHash(std::vector<int> n, int e) {
	uint32_t result = 0;

	result |= (e & 0x00000003);
	for (int i = 0; i < n.size(); i++) {
		result = result << 2;
		result |= (n[i] & 0x00000003);
	}
	return result;
}
#endif

int DoIt(std::vector<int> n, long &time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	int result = -1;
#if STRING_HISTORY
	std::unordered_set<std::string> map;
	std::string finalstate, s;
#else
	//std::vector<uint32_t> map;
	std::unordered_set<uint32_t> map;
	uint32_t finalstate, s;
#endif
	std::queue<FuncCall> bfs;

	begin_time = std::chrono::steady_clock::now();

#if STRING_HISTORY
	for (int i = 0; i <= n.size(); i++) {
		finalstate += '3';
	}
#else
	std::vector<int> final(n.size(), 3);
	finalstate = GetHash(final, 3);
#endif
	FuncCall funccall(n, 0, 0);
	bfs.push(funccall);
	while (!bfs.empty()) {
		FuncCall f = bfs.front();
		bfs.pop();
		if (f.e < 0 || f.e > 3)
			continue; //elevator outside building
		sortx(f.n);
		if (!ok(f.n))
			continue; //microship gets fried
#if STRING_HISTORY
		s = getStr(f.n, f.e);
		if (map.find(s) != map.end())
			continue; //state we've already been to.
		map.emplace(s);
		if (s.compare(finalstate) == 0) { //found final state!
			result = f.k;
			break;
		}
#else
		s = GetHash(f.n, f.e);
		//if (std::find(map.begin(), map.end(), s) != map.end())
		if (map.find(s) != map.end())
			continue; //state we've already been to.
		//map.push_back(s);
		map.emplace(s);
		if (finalstate == s) {
			result = f.k;
			break;
		}
#endif
		for (int i = 0; i < f.n.size(); i++) {
			if (f.n[i] != f.e)
				continue;
			f.n[i]--;
			FuncCall fc1(f.n, f.k + 1, f.e - 1);
			bfs.push(fc1);
			bool mvnxt = (i % 2 == 0) && (f.n[i + 1] == f.e);
			if (mvnxt) {
				f.n[i + 1]--;
				FuncCall fc2(f.n, f.k + 1, f.e - 1);
				bfs.push(fc2);
				f.n[i + 1]++;
			}
			f.n[i] += 2;
			FuncCall fc3(f.n, f.k + 1, f.e + 1);
			bfs.push(fc3);
			if (mvnxt) {
				f.n[i + 1]++;
				FuncCall fc4(f.n, f.k + 1, f.e + 1);
				bfs.push(fc4);
				f.n[i + 1]--;
			}
			f.n[i]--;

			for (int j = i + 2; j < f.n.size(); j += 2) {
				if (f.n[j] != f.e)
					continue;
				f.n[i]--;
				f.n[j]--;
				FuncCall fc5(f.n, f.k + 1, f.e - 1);
				bfs.push(fc5);
				f.n[i] += 2;
				f.n[j] += 2;
				FuncCall fc6(f.n, f.k + 1, f.e + 1);
				bfs.push(fc6);
				f.n[i]--;
				f.n[j]--;
			}
		}
	}

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return result;
}

int main(void) {
	long time = 0, t1 = 0, t2 = 0;
	std::vector<int> data;
	std::cout << "=== Advent of Code 2016 - day 17 ====" << std::endl;

#if TEST
	std::cout << "--- test ---" << std::endl;
	data.clear();
	data.push_back(0);
	data.push_back(1);
	data.push_back(0);
	data.push_back(2);

	test = DoIt(data, time);
	std::cout << "Result is " << test << " (" << time << "ms)" << std::endl;
#endif

	std::cout << "--- part 1 ---" << std::endl;
	data.clear();
	data.push_back(0);
	data.push_back(0);
	data.push_back(2);
	data.push_back(1);
	data.push_back(2);
	data.push_back(1);
	data.push_back(2);
	data.push_back(1);
	data.push_back(2);
	data.push_back(1);
	result1 = DoIt(data, t1);
	std::cout << "Result is " << result1 << " (" << t1 << "ms)" << std::endl;

	std::cout << "--- part 2 ---" << std::endl;
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);
	data.push_back(0);
	result2 = DoIt(data, t2);
	std::cout << "Result is " << result2 << " (" << t2 << "ms)" << std::endl;
}
