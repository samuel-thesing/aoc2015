#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "05"

int solve(const std::string &input) {
	auto lines = split(input, "\n");
	int nice_words = 0;
	for (const auto &line : lines) {
		bool double_pair = false;
		bool mirror_pair = false;
		for (int i = 0; i < line.size()-2; i++) {
			if (line[i] == line[i+2]) {
				mirror_pair = true;
			}

			auto pair = line.substr(i, 2);
			if (line.find(pair, i+2) != std::string::npos) {
				double_pair = true;
			}
		}

		if (mirror_pair && double_pair)
			nice_words++;
	}

	return nice_words;
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
		{"t3.txt", 2},
		{"t4.txt", 0}
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