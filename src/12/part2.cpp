#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "12"

int solve(const std::string &input) {
	std::vector<char> stack;
	std::vector<int> stackSum;
	stackSum.push_back(0);
	// "red" property could appear later on
	// only add sum of current object after fully traversing it

	std::unordered_set<int> red{};
	size_t pos = input.find("\"red\"");
	red.emplace(pos);

	while (pos != std::string::npos) {
		pos = input.find("\"red\"", pos+1);
		red.emplace(pos);
	}

	std::string number;
	bool red_state = false;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '{' || input[i] == '[') {
			stack.push_back(input[i]);
			stackSum.push_back(0);
		} else if (input[i] == '}' || input[i] == ']') {
			if (!red_state)
				stackSum[stackSum.size()-2] += stackSum.back();
			stackSum.pop_back();

			if (stack.back() == 'r') {
				stack.pop_back();
				red_state = false;
			} else{

			}
			stack.pop_back();
		}

		if (red_state) continue;

		if (red.contains(i) && stack.back() == '{') {
			stack.push_back('r');
			red_state = true;
		} else if (input[i] == '-' || isDigit(input[i])) {
			number += input[i];
		} else if (!number.empty()) {
			stackSum.back() += std::stoi(number);
			number = "";
		}
	}

	return stackSum.back();
}

bool test(const std::string &filename, int expected) {
	std::string input = read_file(filename);
	auto result = solve(input);
	if (result == expected) return true;

	Logger::error("{} failed. Expected {} but got {}", filename, expected, result);
	return false;
}

int main(int argc, char** argv) {
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;
	std::vector<std::pair<std::string, int>> test_files = {
		{"t1.txt", 6},
		{"t2.txt", 4},
		{"t4.txt", 6},
		{"t5.txt", 0},
	};
	bool test_failed = false;
	for (const auto& [test_file, expected_result] : test_files) {
		test_failed |= !test(test_file, expected_result);
	}
	if (test_failed) {
		Logger::critical("Aborting after failed tests");
	}
	Logger::info("All tests passed");

	std::string input = read_file("i1.txt");
	auto result = solve(input);
	std::cout << result << std::endl;
}