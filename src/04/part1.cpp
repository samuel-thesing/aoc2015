#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "04"

#include "MD5.h"

int solve(const std::string &input) {
	MD5 md5;
	for (int i = 1; i < 10000000; i++) {
		if (md5(input + std::to_string(i)).starts_with("00000")) {
			return i;
		}
	}

	return 0;
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
		{"t1.txt", 609043},
		{"t2.txt", 1048970}
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