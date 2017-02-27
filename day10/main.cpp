#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

//#define TEST 1

#ifdef TEST
const int part1_val1 = 5;
const int part1_val2 = 2;
const std::string input_filename = "input-test.txt";
#else
const int part1_val1 = 61;
const int part1_val2 = 17;
const std::string input_filename = "input.txt";
#endif

std::regex regex_number("\\d+");

typedef enum { OUT_EMPTY,
			   OUT_BOT,
			   OUT_OUTPUT } OUT_TYPE;

class Bot {
  public:
	Bot();
	Bot(std::string instruction);
	int GetId();
	int GetLowValue();
	int GetLowTarget();
	int GetHighTarget();
	int GetHighValue();
	bool IsReady();
	OUT_TYPE GetLowTargetType();
	OUT_TYPE GetHighTargetType();
	void SetValue(int value);
	bool HandlesValues(int val1, int val2);

  private:
	int id, low, high, val[2], val_cnt;
	OUT_TYPE low_type, high_type;
};

Bot::Bot() {
	id = -1;
	low = 0;
	high = 0;
	low_type = OUT_TYPE::OUT_EMPTY;
	high_type = OUT_TYPE::OUT_EMPTY;
	val_cnt = 0;
}

Bot::Bot(std::string instruction) {
	std::regex regex_bot("bot");
	std::regex regex_output("output");
	std::regex regex_low("gives low to");
	std::regex regex_high("and high to");
	std::smatch sm;
	std::string strlow, strhigh;

	val_cnt = 0;
	val[0] = 0;
	val[1] = 0;
	regex_search(instruction, sm, regex_number);
	id = atoi(sm[0].str().c_str());
	instruction = sm.suffix().str();

	regex_search(instruction, sm, regex_high);
	strhigh = sm.suffix().str();
	strlow = sm.prefix().str();

	regex_search(strlow, sm, regex_low);
	strlow = sm.suffix().str();

	if (regex_search(strlow, sm, regex_bot)) {
		low_type = OUT_TYPE::OUT_BOT;
	} else {
		regex_search(strlow, sm, regex_output);
		low_type = OUT_TYPE::OUT_OUTPUT;
	}
	strlow = sm.suffix().str();
	regex_search(strlow, sm, regex_number);
	low = atoi(sm[0].str().c_str());

	if (regex_search(strhigh, sm, regex_bot)) {
		high_type = OUT_TYPE::OUT_BOT;
	} else {
		regex_search(strhigh, sm, regex_output);
		high_type = OUT_TYPE::OUT_OUTPUT;
	}
	strhigh = sm.suffix().str();
	regex_search(strhigh, sm, regex_number);
	high = atoi(sm[0].str().c_str());
}

int Bot::GetId() {
	return id;
}

int Bot::GetHighTarget() {
	return high;
}

int Bot::GetLowTarget() {
	return low;
}

int Bot::GetHighValue() {
	return (val[0] > val[1] ? val[0] : val[1]);
}

int Bot::GetLowValue() {
	return (val[0] < val[1] ? val[0] : val[1]);
}

bool Bot::IsReady() {
	return val_cnt == 2;
}

void Bot::SetValue(int value) {
	if (!IsReady()) {
		val[val_cnt] = value;
		val_cnt++;
	}
}

OUT_TYPE Bot::GetLowTargetType() {
	return low_type;
}

OUT_TYPE Bot::GetHighTargetType() {
	return high_type;
}

bool Bot::HandlesValues(int val1, int val2) {
	return ((val1 == val[0]) && (val2 == val[1])) || ((val1 == val[1]) && (val2 == val[0]));
}
//---------------------

bool CheckBotInstruction(std::string instruction) {
	std::regex bot_template("bot \\d+ gives low to (bot|output) \\d+ and high to (bot|output) \\d+");
	std::smatch sm;

	return regex_search(instruction, sm, bot_template);
}

bool DecodeValueInstruction(std::string instruction, int &value, int &bot) {
	std::regex value_template("value \\d+ goes to bot \\d+");
	std::smatch sm;

	if (regex_search(instruction, sm, value_template)) {
		if (regex_search(instruction, sm, regex_number)) {
			value = atoi(sm[0].str().c_str());
			instruction = sm.suffix().str();
			if (regex_search(instruction, sm, regex_number)) {
				bot = atoi(sm[0].str().c_str());
				return true;
			}
		}
	}
	return false;
}

int main(void) {
	std::ifstream input;
	std::string line;
	int result1, result2, cnt, val1, val2, bot_number;
	std::map<int, std::vector<int>> values;
	std::map<int, Bot> bots;
	std::map<int, int> outputs;

	std::cout << "=== Advent of Code 2016 - day 10 ====" << std::endl;
	std::cout << "--- part 1 ---" << std::endl;

	input.open(input_filename, std::ifstream::in);

	if (input.fail()) {
		std::cout << "Error opening input file.\n";
		return -1;
	}

	result1 = 0;
	result2 = 0;
	cnt = 0;
	values.clear();
	bots.clear();
	outputs.clear();

	while (std::getline(input, line)) {
		cnt++;
		switch (line[0]) {
			case 'v':
				if (DecodeValueInstruction(line, val1, bot_number)) {
					if (values.find(bot_number) == values.end()) {
						std::vector<int> list;

						list.push_back(val1);
						values[bot_number] = list;
					} else {
						values[bot_number].push_back(val1);
					}

				} else {
					return -1;
				}
				break;
			case 'b':
				if (CheckBotInstruction(line)) {
					Bot bot(line);

					bots[bot.GetId()] = bot;
				} else {
					return -1;
				}
				break;
			default:
				std::cout << "Invalid instruction on line " << cnt << std::endl;
				return -1;
		}
	}

	if (input.is_open()) {
		input.close();
	}

	for (auto const &ent1 : values) {
		if (bots.find(ent1.first) != bots.end()) {
			for (int i = 0; i < ent1.second.size(); i++) {
				if (!bots[ent1.first].IsReady()) {
					bots[ent1.first].SetValue(ent1.second[i]);
				} else {
					int x = 77;
				}
			}
			//			if (bots[ent1.first].IsReady() && bots[ent1.first].HandlesValues(part1_val1, part1_val2)){
			//				result1 = bots[ent1.first].GetId();
			//			}
		} else {
			int x = 77;
		}
	}

	bool finished = false;
	bool stuck = false;
	bool outputs_updated = false, outputs_finished = false;

	while (!(finished && outputs_finished) && !stuck) {
		int bot_ready, id, val_id;
		stuck = true;
		for (auto &b : bots) {
			id = b.first;
			outputs_updated = false;
			if (b.second.IsReady()) {
				bot_ready = id;
				stuck = false;

				if (b.second.HandlesValues(part1_val1, part1_val2)) {
					finished = true;
					result1 = b.second.GetId();
					//break;
				}

				if (bots[id].GetLowTargetType() == OUT_TYPE::OUT_BOT) {
					val_id = bots[id].GetLowTarget();
					if (bots.find(val_id) != bots.end()) {
						if (!bots[val_id].IsReady()) {
							bots[val_id].SetValue(bots[id].GetLowValue());
						}
					}
				} else if (bots[id].GetLowTargetType() == OUT_TYPE::OUT_OUTPUT) {
					outputs[bots[id].GetLowTarget()] = bots[id].GetLowValue();
					outputs_updated = true;
				}

				if (bots[id].GetHighTargetType() == OUT_TYPE::OUT_BOT) {
					val_id = bots[id].GetHighTarget();
					if (bots.find(val_id) != bots.end()) {
						if (!bots[val_id].IsReady()) {
							bots[val_id].SetValue(bots[id].GetHighValue());
						}
					}
				} else if (bots[id].GetHighTargetType() == OUT_TYPE::OUT_OUTPUT) {
					outputs[bots[id].GetHighTarget()] = bots[id].GetHighValue();
					outputs_updated = true;
				}
			}

			if (outputs_updated && !outputs_finished) {
				if (outputs.find(0) != outputs.end()) {
					if (outputs.find(1) != outputs.end()) {
						if (outputs.find(2) != outputs.end()) {
							result2 = outputs[0] * outputs[1] * outputs[2];
							outputs_finished = true;
						}
					}
				}
			}
			if (!stuck) {
				bots.erase(bot_ready);
				break;
			}
		}
	}

	std::cout << "Result is " << result1 << std::endl;
	std::cout << "--- part 2 ---" << std::endl;
	std::cout << "Result is " << result2 << std::endl;
}
