#include <iostream>
#include <string>
#include <openssl/md5.h>

char buffer[101];
unsigned char hash[MD5_DIGEST_LENGTH];
const std::string input = "abbhdwsy";

int main(void) {
	std::string result1, result2;
	int number = 0, size;
	bool hash1_found = false;
	char c;

	std::cout << "=== Advent of Code 2016 - day 5 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	result1.clear();
	result2.clear();
	for (int i = 0; i < 8; i++) {
		hash1_found = false;
		
		while (!hash1_found) {
			number++;
			sprintf(buffer, "%s%d", input.c_str(), number);
			size = strlen(buffer);
			MD5((const unsigned char *)buffer, size, hash);
			if (hash[0] == 0 && hash[1] == 0) {
				if ((hash[2] & 0xF0) == 0)  {
					c = hash[2] & 0x0F;
					if ((c >= 0x0A ) && (c <= 0x0F)){
						c += 'A' - 0x0A;
					}
					else {
						c += '0';
					}
					hash1_found = true;
					result1.push_back(c);
				}
/*				if ((hash[2] == 0) && (result2 == 0)) {
					result2 = number;
				}*/
			}
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}

