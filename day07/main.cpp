#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool HasABBA(std::string part) {
	if (part.size() >= 4) {
		for (int i = 1; i < part.size() - 2; i++) {
			if (part[i] == part[i + 1]) {
				if ((part[i - 1] != part[i]) && (part[i - 1] == part[i + 2])) {
					std::cout << "ABBA found" << std::endl;
					return true;
				}
			}
		}
		return false;
	} else {
		return false;
	}
}

void GetABAandBAB(std::string part, std::vector<std::string> &result) {

	for (int i = 0; i < part.size() - 2; i++) {
		if ((part[i] == part[i + 2]) && (part[i] != part[i + 1])) {
			result.push_back(part.substr(i, 3));
		}
	}
}

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, result2, pos1, pos2, start, cnt;
	bool tls, tls_hyper, ababab;

	std::cout << "=== Advent of Code 2016 - day 7 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	// input.open("input-test.txt", std::ifstream::in);
	// input.open("input-test2.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;
	result1 = 0;
	result2 = 0;
	while (std::getline(input, line)) {
		std::vector<std::string> abas, babs;
		std::string part;

		cnt++;
		start = 0;
		tls = false;
		tls_hyper = false;
		ababab = false;
		pos1 = line.find('[');
		while (pos1 != std::string::npos) {
			pos2 = line.find(']', pos1 + 1);
			if (pos2 == std::string::npos) {
				std::cout << "Invalid IP7 address at line " << cnt << std::endl;
				return -1;
			}
			part = line.substr(start, pos1 - start);
			if (HasABBA(part)) {
				tls = true;
			}
			GetABAandBAB(part, abas);
			part = line.substr(pos1 + 1, pos2 - pos1 - 1);
			if (HasABBA(part)) {
				tls_hyper = true;
			}
			GetABAandBAB(part, babs);
			start = pos2 + 1;
			pos1 = line.find('[', start);
		}
		if (!tls_hyper && !tls) {
			tls = HasABBA(line.substr(start));
		}
		GetABAandBAB(line.substr(start), abas);
		if (tls && !tls_hyper) {
			result1++;
		}
		for (int i = 0; i < abas.size(); i++) {
			for (int j = 0; j < babs.size(); j++) {
				if ((abas[i].size() != 3) || (babs[j].size() != 3)) {
					continue;
				}
				if ((abas[i][0] == babs[j][1]) && (abas[i][1] == babs[j][0]) &&
					(abas[i][2] == babs[j][1]) && (abas[i][1] == babs[j][2])) {
					ababab = true;
					break;
				}
			}
			if (ababab) {
				break;
			}
		}
		if (ababab) {
			result2++;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
