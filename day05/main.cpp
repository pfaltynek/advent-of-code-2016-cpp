#include <cstdio>
#include <iostream>
#include <openssl/md5.h>
#include <string.h>
#include <string>

char buffer[101];
unsigned char hash[MD5_DIGEST_LENGTH];
const std::string input = "abbhdwsy";

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
	bool finished = false;

	std::cout << "=== Advent of Code 2016 - day 5 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1.clear();
	result2 = "________";

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
				}
				if (val1 < 8) {
					if (result2[val1] == '_') {
						result2[val1] = HalfByteToHex(val2);
					}
				}
			}
		}
		finished =
			(result1.size() == 8) && (result2.find('_') == std::string::npos);
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
