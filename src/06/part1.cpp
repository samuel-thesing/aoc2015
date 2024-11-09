#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>
#include <set>

#define YEAR "2015"
#define DAY "06"

struct Point {
	int x;
	int y;

	bool operator<(const Point &other) const {
		if (x == other.x)
			return y < other.y;
		return x < other.x;
	}
};

Point str_to_point(std::string str) {
	auto pair = split<int>(str, ",", [](std::string pos) {
		return std::stoi(pos);
	});

	return {pair[0], pair[1]};
}

int solve(const std::string &input) {
	std::array<bool, 1000000> lights{};
	int size = 1000;
	lights.fill(false);

	auto lines = split(input, "\n");
	for (const auto &line : lines) {
		auto words = split(line, " ");
		int mode = 0;
		Point start;
		Point end;
		if (line[1] == 'o') {
			mode = 2;
			start = str_to_point(words[1]);
			end = str_to_point(words[3]);
		} else {
			if (line[6] == 'n') {
				mode = 1;
			} else {
				mode = 0;
			}
			start = str_to_point(words[2]);
			end = str_to_point(words[4]);
		}

		for (int y = start.y; y <= end.y; y++) {
			int offy = y * size;
			for (int x = start.x; x <= end.x; x++) {
				if (mode == 2) {
					lights[offy+x] = !lights[offy+x];
				} else {
					lights[offy+x] = mode;
				}
			}
		}
	}

	int count = 0;
	for (int i = 0; i < size*size; i++) {
		count += lights[i];
	}

	return count;
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
		{"t1.txt", 1000000},
		{"t2.txt", 1000}
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