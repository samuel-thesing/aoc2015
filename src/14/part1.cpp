#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "14"

int solve(const std::string &input) {
	auto lines = split(input, "\n");

	std::regex pattern(".+ can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");

	int max_dist = 0;

	for (const auto &line : lines) {
		const auto& [speed, duration, rest] = extract_data<int, int, int>(pattern, line);

		int distance = 0;
		int traveling = 0;
		for (int i = 0; i < 2503; i++) {
			traveling++;
			distance += speed;
			if (traveling == duration) {
				traveling = 0;
				i += rest;
			}
		}
		max_dist = max(max_dist, distance);
	}

	return max_dist;
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
		{"t1.txt", 2660}
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