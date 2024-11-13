#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "16"

std::string solve(const std::string &input) {
	std::unordered_map<std::string, int> map = {
		{"children", 3},
		{"cats", 7},
		{"samoyeds", 2},
		{"pomeranians", 3},
		{"akitas", 0},
		{"vizslas", 0},
		{"goldfish", 5},
		{"trees", 3},
		{"cars", 2},
		{"perfumes", 1}
	};

	std::unordered_set<std::string> lesser = {"pomeranians", "goldfish"};
	std::unordered_set<std::string> greater = {"cats", "trees"};

	std::regex pattern("(.+): (\\d+)");
	auto lines = split(input, "\n");


	for (const auto &line : lines) {
		auto [sue, parts] = split_once(line, ":");
		auto part_vec = split(parts, ", ");
		for (const auto& part : part_vec) {
			const auto [name, count] = extract_data<std::string, int>(pattern, part);
			auto ref_count = map[name];
			if (lesser.contains(name)) {
				if (ref_count <= count) {
					goto end_outer;
				}
			} else if (greater.contains(name)) {
				if (ref_count >= count) {
					goto end_outer;
				}
			} else if (ref_count != count) {
				goto end_outer;
			}
		}

		return sue;

		end_outer:;
	}

	Logger::critical("No solution found");
}

bool test(const std::string &filename, std::string expected) {
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
	std::vector<std::pair<std::string, std::string>> test_files = {
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

	// 212 low
}