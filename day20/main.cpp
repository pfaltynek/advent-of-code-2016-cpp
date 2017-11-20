#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define TEST 0

typedef struct {
	uint32_t first, last;
} IP_RANGE;

typedef std::vector<IP_RANGE>::iterator IT;

void InsertRange(IP_RANGE new_range, std::vector<IP_RANGE> &ranges) {
	IT it1;
	it1 = ranges.begin();

	while (it1 != ranges.end()) {
		if ((*it1).first >= new_range.first) {
			break;
		}
		it1++;
	}

	ranges.insert(it1, new_range);
}

void OptimizeRanges(std::vector<IP_RANGE> &ranges) {
	IT it1, it2;

	it1 = ranges.begin();
	it2 = it1 + 1;
	//4258853578
	while (it2 != ranges.end()) {
		if ((it1->first == 4258853578) || (it2->first == 4258853578)) {
			bool fnd = true;
		}
		if ((it1->last) >= (it2->first - 1)) {
			it1->last = (it1->last > it2->last) ? it1->last : it2->last;
			ranges.erase(it2);
			it2 = it1 + 1;
		} else {
			it1++;
			it2++;
		}
	}
}

uint32_t GetWhiteIPCount(std::vector<IP_RANGE> ranges) {
	IT it;
	uint32_t result = 0;
	long long next_check = 0;

	if (ranges.empty()) {
		return UINT32_MAX;
	}

	it = ranges.begin();

	while ((it != ranges.end()) || (next_check > UINT32_MAX)) {
		if (it->first > next_check) {
			result += it->first - next_check;
		}
		next_check = it->last + 1;
		it++;
	}
	if (next_check < UINT32_MAX) {
		result += UINT32_MAX - next_check + 1;
	}

	return result;
}

bool GetFirstWhiteIP(std::vector<IP_RANGE> ranges, uint32_t &result) {
	IT it;
	uint32_t next_check = 0;

	it = ranges.begin();
	while (it != ranges.end()) {
		if (it->last == UINT32_MAX) {
			return false;
		}
		if (it->first > next_check) {
			result = next_check;
			return true;
		} else {
			next_check = it->last + 1;
			it++;
		}
	}
	return false;
}

int main(void) {
	std::ifstream input;
	std::string line;
	uint32_t result1, result2, test, cnt, test2;
	std::regex data_pattern("^(\\d+)-(\\d+)$");
	std::smatch sm;
	std::vector<IP_RANGE> data;
	IP_RANGE x;

	std::cout << "=== Advent of Code 2016 - day 20 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	test = 0;
	test2 = 0;
	cnt = 0;

#if TEST
	data.clear();
	x.first = 5;
	x.last = 8;
	InsertRange(x, data);
	x.first = 0;
	x.last = 2;
	InsertRange(x, data);
	x.first = 4;
	x.last = 7;
	InsertRange(x, data);
	OptimizeRanges(data);
	if (GetFirstWhiteIP(data, test)) {
		std::cout << "Result is " << test << std::endl;
	} else {
		std::cout << "Result does not exist." << std::endl;
	}
	test2 = GetWhiteIPCount(data);
#endif

	data.clear();

	while (std::getline(input, line)) {
		cnt++;
		if (line.empty()) {
			continue;
		}
		if (regex_match(line, sm, data_pattern)) {
			IP_RANGE ipr;

			unsigned long int f, l;

			f = strtoul(sm.str(1).c_str(), NULL, 10);
			l = strtoul(sm.str(2).c_str(), NULL, 10);

			ipr.first = (uint32_t)f;
			ipr.last = (uint32_t)l;
			if (ipr.first > ipr.last) {
				int z = 11;
			}
			InsertRange(ipr, data);
		} else {
			std::cout << "Error decoding data of line " << cnt << std::endl;
			return -1;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	OptimizeRanges(data);

	if (GetFirstWhiteIP(data, result1)) {
		std::cout << "Result is " << result1 << std::endl;
	} else {
		std::cout << "Result does not exist." << std::endl;
	}
	std::cout << "--- part 2 ---" << std::endl;
	result2 = GetWhiteIPCount(data);
	std::cout << "Result is " << result2 << std::endl;
}
