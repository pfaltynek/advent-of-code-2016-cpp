#include <cstdio>
#include <iostream>
#include <openssl/md5.h>
#include <string.h>
#include <string>
# include <ctime>

char buffer[101];
unsigned char hash[MD5_DIGEST_LENGTH];
const std::string input = "abbhdwsy";
const std::string hour_glass = "\\|/-";
const char unknown_char = '*';

char HalfByteToHex(int val) {
	char c;

	c = val & 0x0F;
	if ((c >= 0x0A) && (c <= 0x0F)) {
		c += 'a' - 0x0A;
	} else {
		c += '0';
	}

	return c;
}

int main(void) {
	std::string result1, result2;
	int number = 0, size, val1, val2;
	int hour_glass_idx = 0;
	bool finished = false;
	bool update_console = false;
	clock_t current_time, prev_time = clock();

	std::cout << std::endl;
	std::cout << "=== Advent of Code 2016 - day 5 ====" << std::endl;
	std::cout << "Decoding passwords:" << std::endl;

	result1.clear();
	result2.clear();
	for(int i = 0; i < 8; i++){
		result2.push_back(unknown_char);
	}

	while (!finished) {
		number++;
		sprintf(buffer, "%s%d", input.c_str(), number);
		size = strlen(buffer);
		MD5((const unsigned char *)buffer, size, hash);
		if (hash[0] == 0 && hash[1] == 0) {
			if ((hash[2] & 0xF0) == 0) {
				val1 = hash[2] & 0x0F;
				val2 = hash[3] / 0x10;
				if (result1.size() < 8) {
					result1.push_back(HalfByteToHex(val1));
					update_console = true;
				}
				if (val1 < 8) {
					if (result2[val1] == unknown_char) {
						result2[val1] = HalfByteToHex(val2);
						update_console = true;
					}
				}
			}
		}
		current_time = clock();
		if ((current_time - prev_time) > (CLOCKS_PER_SEC/4)){
			hour_glass_idx += ((current_time - prev_time) / (CLOCKS_PER_SEC/4));
			hour_glass_idx %= hour_glass.size();
			prev_time = current_time;
			update_console = true; 
		}
		if (update_console) {
			std::cout << "\r  ";
			std::cout << hour_glass[hour_glass_idx];
			std::cout << "  part 1: ";
			std::cout << result1;
			for (int i = result1.size(); i < 8; i++) {
				std::cout << unknown_char;
			}
			std::cout << "    part 2: " << result2;
			std::cout << "  " << hour_glass[hour_glass_idx] << std::flush;
			update_console = false;
		}
		finished =
			(result1.size() == 8) && (result2.find(unknown_char) == std::string::npos);
	}

	std::cout << std::endl << std::endl << "Decoding finished." << std::endl;
}
