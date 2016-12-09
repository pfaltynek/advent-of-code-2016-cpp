#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#define DEBUG_OUTPUT 0
const std::string col_rotate = "rotate column x=";
const std::string row_rotate = "rotate row y=";
const std::string rect = "rect ";
const std::string row_col_divier = " by ";
const std::string rect_divier = "x";
const int MAX_COLUMN = 50;
const int MAX_ROW = 6;

unsigned char display[MAX_COLUMN][MAX_ROW];

void ShowDisplay(void) {
	std::cout << std::endl;
	for (int j = 0; j < MAX_ROW; j++) {
		for (int i = 0; i < MAX_COLUMN; i++) {
			std::cout << (display[i][j] ? '#' : '.');
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, cnt;

	std::cout << "=== Advent of Code 2016 - day 8 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);
	// input.open("input-test.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;
	result1 = 0;
	memset(display, sizeof(display), 0);

#if DEBUG_OUTPUT
	ShowDisplay();
#endif

	while (std::getline(input, line)) {
		std::string part, l, r;
		int pos, v1, v2, tmp;

		cnt++;

#if DEBUG_OUTPUT
		std::cout << "Processing line " << cnt << ": " << line << std::endl;
#endif

		if (line.find(row_rotate) == 0) {
			part = line.substr(row_rotate.size());
			pos = part.find(row_col_divier);
			if (pos == std::string::npos) {
				std::cout
					<< "Unknown row rotation instruction parameters at line "
					<< cnt << std::endl;
				return -1;
			}
			l = part.substr(0, pos);
			r = part.substr(pos + row_col_divier.size());
			if (l.empty() || r.empty()) {
				std::cout << "Empty row rotation instruction parameter at line "
						  << cnt << std::endl;
				return -1;
			}
			v1 = atoi(l.c_str());
			v2 = atoi(r.c_str());
			if ((v1 >= MAX_ROW) || (v1 < 0) || (v2 < 0)) {
				std::cout
					<< "Invalid row rotation instruction parameters at line "
					<< cnt << std::endl;
				return -1;
			}
			for (int j = 0; j < v2; j++) {
				tmp = display[MAX_COLUMN - 1][v1];
				for (int i = MAX_COLUMN - 1; i > 0; i--) {
					display[i][v1] = display[i - 1][v1];
				}
				display[0][v1] = tmp;
			}
		} else if (line.find(col_rotate) == 0) {
			part = line.substr(col_rotate.size());
			pos = part.find(row_col_divier);
			if (pos == std::string::npos) {
				std::cout
					<< "Unknown column rotation instruction parameters at line "
					<< cnt << std::endl;
				return -1;
			}
			l = part.substr(0, pos);
			r = part.substr(pos + row_col_divier.size());
			if (l.empty() || r.empty()) {
				std::cout
					<< "Empty column rotation instruction parameter at line "
					<< cnt << std::endl;
				return -1;
			}
			v1 = atoi(l.c_str());
			v2 = atoi(r.c_str());
			if ((v1 >= MAX_COLUMN) || (v1 < 0) || (v2 < 0)) {
				std::cout
					<< "Invalid column rotation instruction parameters at line "
					<< cnt << std::endl;
				return -1;
			}
			for (int j = 0; j < v2; j++) {
				tmp = display[v1][MAX_ROW - 1];
				for (int i = MAX_ROW - 1; i > 0; i--) {
					display[v1][i] = display[v1][i - 1];
				}
				display[v1][0] = tmp;
			}
		} else if (line.find(rect) == 0) {
			part = line.substr(rect.size());
			pos = part.find(rect_divier);
			if (pos == std::string::npos) {
				std::cout << "Unknown rectangle instruction parameters at line "
						  << cnt << std::endl;
				return -1;
			}
			l = part.substr(0, pos);
			r = part.substr(pos + rect_divier.size());
			if (l.empty() || r.empty()) {
				std::cout << "Empty rectangle instruction parameter at line "
						  << cnt << std::endl;
				return -1;
			}
			v1 = atoi(l.c_str());
			v2 = atoi(r.c_str());
			if ((v1 > MAX_COLUMN) || (v2 > MAX_ROW) || (v1 <= 0) || (v2 <= 0)) {
				std::cout << "Invalid rectangle instruction parameter at line "
						  << cnt << std::endl;
				return -1;
			}
			for (int i = 0; i < v1; i++) {
				for (int j = 0; j < v2; j++) {
					display[i][j] = 1;
				}
			}
		} else {
			std::cout << "Unknown instruction at line " << cnt << std::endl;
			return -1;
		}

#if DEBUG_OUTPUT
		ShowDisplay();
#endif
	}

	if (input.is_open()) {
		input.close();
	}

	for (int i = 0; i < MAX_COLUMN; i++) {
		for (int j = 0; j < MAX_ROW; j++) {
			if (display[i][j]) {
				result1++;
			}
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is:" << std::endl;

#if !DEBUG_OUTPUT
	ShowDisplay();
#endif
}
