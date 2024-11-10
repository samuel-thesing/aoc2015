#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "10"

int solve(const std::string &input) {
	std::string current = input;
	for (int i = 0; i < 50; i++) {
		std::string next = "";
		int count = 0;
		char prev_c = '\0';
		for (char c : current) {
			if (c != prev_c) {
				if (count != 0) {
					next += std::to_string(count) + prev_c;
				}
				count = 1;
				prev_c = c;
			} else {
				count++;
			}
		}
		next += std::to_string(count) + prev_c;
		current = next;
	}

	return current.size();
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
		{"t1.txt", 1166642}
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