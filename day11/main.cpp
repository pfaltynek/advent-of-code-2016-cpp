
#include <algorithm>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

#define FIRST_FLOOR 0
#define FINAL_FLOOR 3

#define GENERATOR 0
#define MICROCHIP 1
int result1, result2;

#define TEST 1

class FuncCall {
  public:
	std::vector<int> n;
	int k;
	int e;
	FuncCall(std::vector<int> n, int e, int k) {
		this->n = std::vector<int>(n);
		this->e = e;
		this->k = k;
	}
};

int DoIt(std::vector<int> n, long time_msec) {
	std::chrono::steady_clock::time_point begin_time, end_time;
	int result = -1;

	begin_time = std::chrono::steady_clock::now();

	end_time = std::chrono::steady_clock::now();
	time_msec = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count();

	return result;
}

int main(void) {

	std::cout << "=== Advent of Code 2016 - day 11 ====" << std::endl;

#if TEST
	std::cout << "--- test ---" << std::endl;

#endif

	std::cout << "--- part 1 ---" << std::endl;

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << result2 << std::endl;
}
