#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

typedef struct {
	unsigned int size, position;
} DAY15_DATA;

int CalculateChineRemainers(std::vector<DAY15_DATA> data) {
	int time = 0;
	bool done;

	do {
		done = true;
		for (int i = 0; i < data.size(); i++) {
			if ((time + data[i].position) % data[i].size){
				done = false;
				time++;
				break;
			}
		}
	} while (!done);

	return time;
}

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, result2, cnt;
	std::regex data_pattern("Disc #(\\d+) has (\\d+) positions; at time=0, it is at position (\\d+).");
	std::smatch sm;
	std::vector<DAY15_DATA> data;
	DAY15_DATA x;

	std::cout << "=== Advent of Code 2016 - day 15 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	cnt = 0;

#if TEST
	data.clear();
	x.size = 5;
	x.position = 0;
	data.push_back(x);
	x.size = 2;
	x.position = 1;
	data.push_back(x);
	result1 = CalculateChineRemainers(data);
#endif

	data.clear();

	while (std::getline(input, line)) {
		cnt++;
		if (regex_match(line, sm, data_pattern)) {
			DAY15_DATA d15;
			int disc, size, position;

			disc = atoi(sm.str(1).c_str());
			size = atoi(sm.str(2).c_str());
			position = atoi(sm.str(3).c_str());
			d15.size = size;
			d15.position = (disc + position) % size;
			data.push_back(d15);
		} else {
			std::cout << "Error decoding data of line " << cnt << std::endl;
			return -1;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	result1 = CalculateChineRemainers(data);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	x.size = 11;
	x.position = (data.size() + 1 + 0) % x.size;
	data.push_back(x);
	result2 = CalculateChineRemainers(data);
	std::cout << "Result is " << result2 << std::endl;
}
