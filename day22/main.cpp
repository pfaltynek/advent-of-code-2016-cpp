#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

typedef struct {
	int x, y, size, used, avail, use_perc;
} DAY22_NODE;

bool DecodeNodeInfo(std::string line, DAY22_NODE &node) {
	std::regex node_info_regex("\\/dev\\/grid\\/node-x(\\d+)-y(\\d+)[[:blank:]]+(\\d+)T[[:blank:]]+(\\d+)T[[:blank:]]+(\\d+)T[[:blank:]]+(\\d+)%$");
	std::smatch sm;

	if (std::regex_match(line, sm, node_info_regex)) {
		//if (std::regex_search(line, sm, node_info_regex)) {
		node.x = atoi(sm.str(1).c_str());
		node.y = atoi(sm.str(2).c_str());
		node.size = atoi(sm.str(3).c_str());
		node.used = atoi(sm.str(4).c_str());
		node.avail = atoi(sm.str(5).c_str());
		node.use_perc = atoi(sm.str(6).c_str());
		return true;
	}
	return false;
}

bool CompareNodesByUsed(DAY22_NODE node1, DAY22_NODE node2) {
	return (node1.used > node2.used);
}

bool CompareNodesByAvail(DAY22_NODE node1, DAY22_NODE node2) {
	return (node1.avail > node2.avail);
}

int GetViableNodesPairCount(std::vector<DAY22_NODE> nodes) {
	std::vector<DAY22_NODE> by_used(nodes), by_avail(nodes);

	std::sort(by_used.begin(), by_used.end(), CompareNodesByUsed);
	std::sort(by_avail.begin(), by_avail.end(), CompareNodesByAvail);

	return 0;
}

int main(void) {
	std::ifstream input;
	std::string line;
	std::vector<DAY22_NODE> data;
	int cnt, result1, result2;

	cnt = 0;
	result1 = 0;
	result2 = 0;

	std::cout << "=== Advent of Code 2016 - day 22 ====" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	data.clear();

	while (std::getline(input, line)) {
		DAY22_NODE node;
		cnt++;
		if (DecodeNodeInfo(line, node)) {
			data.push_back(node);
		} else {
			std::cout << "Line: '" << line << "' ignored." << std::endl;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "--- part 1 ---" << std::endl;
	result1 = GetViableNodesPairCount(data);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;

	std::cout << "Result is " << result2 << std::endl;
}
