#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "17"

int count_solutions(const std::vector<int>& containers, int idx, int missing) {
	if (missing == 0) {
		return 1;
	}

	if (idx >= containers.size()) {
		return 0;
	}

	int sum = count_solutions(containers, idx + 1, missing);

	if (containers[idx] <= missing) {
		sum += count_solutions(containers, idx + 1, missing - containers[idx]);
	}

	return sum;
}

int solve(const std::string &input, int amount) {
	auto lines = split<int>(input, "\n", [](std::string line) {
		return std::stoi(line);
	});

	return count_solutions(lines, 0, amount);

}

template<typename T, typename U>
bool test(const std::string &filename, T expected, U args) {
	std::string input = read_file(filename);
	auto result = solve(input, args);
	if (result == expected) return true;

	Logger::error("{} failed. Expected {} but got {}", filename, expected, result);
	return false;
}

int main(int argc, char** argv) {
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;
	std::vector<std::tuple<std::string, int, int>> test_files = {
		{"t1.txt", 4, 25}
	};
	bool test_failed = false;
	for (const auto& [test_file, expected_result, arguments] : test_files) {
		test_failed |= !test(test_file, expected_result, arguments);
	}
	if (test_failed) {
		Logger::critical("Aborting after failed tests");
	}
	Logger::info("All tests passed");

	std::string input = read_file("i1.txt");
	auto result = solve(input, 150);
	std::cout << result << std::endl;
}