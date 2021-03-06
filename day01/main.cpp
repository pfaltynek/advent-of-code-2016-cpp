#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

const std::string divider = ", ";

bool IsNumeric(std::string num) {
	return (num.find_first_not_of("0123456789") == std::string::npos);
}

int main(void) {
	int result1 = 0, result2 = 0, cnt;
	std::ifstream input;
	std::string line;
	std::string navigation;
	size_t pos, pos_prev;
	int north, east, heading, len;
	int trace_route[200][2];
	bool part2_done = false;

	std::cout << "=== Advent of Code 2016 - day 1 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open("input.txt", std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	cnt = 0;

	navigation.clear();
	while (std::getline(input, line)) {
		navigation += line;
	}

	if (input.is_open()) {
		input.close();
	}

	north = 0;
	east = 0;
	pos = 0;
	pos_prev = 0;
	// 0->N, 1->E, 2->S, 3->W
	heading = 0;
	trace_route[0][0] = 0;
	trace_route[0][1] = 0;
	pos = navigation.find(divider, pos_prev);
	while (pos_prev != std::string::npos) {
		char c;
		int len;

		cnt++;
		if (pos == std::string::npos) {
			line = navigation.substr(pos_prev);
			pos_prev = pos;
		} else {
			line = navigation.substr(pos_prev, pos - pos_prev);
			pos_prev = pos + divider.size();
			pos = navigation.find(", ", pos_prev);
		}
		if (line.size() < 2) {
			std::cout << "Invalid instruction format at position " << cnt
					  << std::endl;
			return -1;
		}
		switch (line[0]) {
			case 'l':
			case 'L':
				heading = (heading + 3) % 4;
				break;
			case 'r':
			case 'R':
				heading = (heading + 1) % 4;
				break;
			default:
				std::cout << "Invalid instruction heading type at position "
						  << cnt << std::endl;
				return -1;
		}
		line = line.substr(1);
		if (!IsNumeric(line)) {
			std::cout << "Invalid instruction distance value at position "
					  << cnt << std::endl;
		}

		len = (atoi(line.c_str()));
		switch (heading) {
			case 0:
				north += len;
				break;
			case 1:
				east += len;
				break;
			case 2:
				north -= len;
				break;
			case 3:
				east -= len;
				break;
		}
		trace_route[cnt][0] = north;
		trace_route[cnt][1] = east;

		if ((cnt > 3) && !part2_done) {
			int n11, n12, e11, e12;
			int n21, n22, e21, e22;
			bool n, e;
			n21 = std::min(trace_route[cnt - 1][0], trace_route[cnt][0]);
			e21 = std::min(trace_route[cnt - 1][1], trace_route[cnt][1]);
			n22 = std::max(trace_route[cnt - 1][0], trace_route[cnt][0]);
			e22 = std::max(trace_route[cnt - 1][1], trace_route[cnt][1]);

			for (int i = 1; i < (cnt - 1); i++) {
				n11 = std::min(trace_route[i - 1][0], trace_route[i][0]);
				e11 = std::min(trace_route[i - 1][1], trace_route[i][1]);
				n12 = std::max(trace_route[i - 1][0], trace_route[i][0]);
				e12 = std::max(trace_route[i - 1][1], trace_route[i][1]);

				n = false;
				e = false;

				if ((n11 == n21) || (n11 == n22) || (n12 == n21) ||
					(n12 == n22)) {
					n = true;
				} else if (n11 < n21) {
					if (n12 > n21) {
						n = true;
					}
				} else {
					if (n22 > n11) {
						n = true;
					}
				}

				if ((e11 == e21) || (e11 == e22) || (e12 == e21) ||
					(e12 == e22)) {
					e = true;
				} else if (e11 < e21) {
					if (e12 > e21) {
						e = true;
					}
				} else {
					if (e22 > e11) {
						e = true;
					}
				}

				if (n & e) {
					bool way1asc, way2asc, way1n, way2n;
					int way1start, way1end, way2start, way2end, way1const, way2const;

					n11 = trace_route[i - 1][0];
					e11 = trace_route[i - 1][1];
					n12 = trace_route[i][0];
					e12 = trace_route[i][1];

					n21 = trace_route[cnt - 1][0];
					e21 = trace_route[cnt - 1][1];
					n22 = trace_route[cnt][0];
					e22 = trace_route[cnt][1];

					if (n11 == n12) {
						way1n = false;
						way1start = e11;
						way1end = e12;
						way1const = n11;
					} else {
						way1n = true;
						way1start = n11;
						way1end = n12;
						way1const = e11;
					}
					way1asc = (way1start < way1end);

					if (n21 == n22) {
						way2n = false;
						way2start = e21;
						way2end = e22;
						way2const = n21;
					} else {
						way2n = true;
						way2start = n21;
						way2end = n22;
						way2const = e21;
					}
					way2asc = (way2start < way2end);

					if (way1asc) {
						if (way2asc) {
							for (int i = way1start; i <= way1end; i++) {
								for (int j = way2start; j <= way2end; j++) {
									if (way1n == way2n) {
										if ((i == j) &&
											(way1const == way2const)) {
											result2 = i + way1const;
											part2_done = true;
											break;
										}
									} else {
										if ((i == way2const) &&
											(way1const == j)) {
											result2 = i + way2const;
											part2_done = true;
											break;
										}
									}
								}
								if (part2_done) {
									break;
								}
							}
						} else {
							for (int i = way1start; i <= way1end; i++) {
								for (int j = way2start; j >= way2end; j--) {
									if (way1n == way2n) {
										if ((i == j) &&
											(way1const == way2const)) {
											result2 = i + way1const;
											part2_done = true;
											break;
										}
									} else {
										if ((i == way2const) &&
											(way1const == j)) {
											result2 = abs(i) + abs(way1const);
											part2_done = true;
											break;
										}
									}
								}
								if (part2_done) {
									break;
								}
							}
						}
					} else {
						if (way2asc) {
							for (int i = way1start; i >= way1end; i--) {
								for (int j = way2start; j <= way2end; j++) {
									if (way1n == way2n) {
										if ((i == j) &&
											(way1const == way2const)) {
											result2 = i + way1const;
											part2_done = true;
											break;
										}
									} else {
										if ((i == way2const) &&
											(way1const == j)) {
											result2 = i + way2const;
											part2_done = true;
											break;
										}
									}
								}
								if (part2_done) {
									break;
								}
							}
						} else {
							for (int i = way1start; i >= way1end; i--) {
								for (int j = way2start; j >= way2end; j--) {
									if (way1n == way2n) {
										if ((i == j) &&
											(way1const == way2const)) {
											result2 = i + way1const;
											part2_done = true;
											break;
										}
									} else {
										if ((i == way2const) &&
											(way1const == j)) {
											result2 = i + way2const;
											part2_done = true;
											break;
										}
									}
								}
								if (part2_done) {
									break;
								}
							}
						}
					}
				}
				if (part2_done){
					break;
				}
			}
		}
	}

	result1 = abs(north) + abs(east);
	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
