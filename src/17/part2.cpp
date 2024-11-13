#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "17"

void check_solution(int num_containers, std::pair<int, int>& result) {
	if (num_containers > result.first) return;
	if (num_containers < result.first) {
		result.first = num_containers;
		result.second = 1;
	} else {
		result.second++;
	}
}

void count_solutions(const std::vector<int>& containers, int idx, int missing, int num_containers, std::pair<int, int>& result) {
	if (missing == 0) {
		check_solution(num_containers, result);
		return;
	}

	if (idx >= containers.size()) {
		return;
	}

	count_solutions(containers, idx + 1, missing, num_containers, result);

	if (containers[idx] <= missing) {
		count_solutions(containers, idx + 1, missing - containers[idx], num_containers+1, result);
	}
}

int solve(const std::string &input, int amount) {
	auto lines = split<int>(input, "\n", [](std::string line) {
		return std::stoi(line);
	});

	auto result = std::make_pair<int, int>(lines.size(), 0);
	count_solutions(lines, 0, amount, 0, result);
	return result.second;
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
		{"t1.txt", 3, 25}
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