#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>
#include <set>

#define YEAR "2015"
#define DAY "03"

struct Point {
	int x;
	int y;

	bool operator<(const Point &other) const {
		if (x == other.x)
			return y < other.y;
		return x < other.x;
	}
};

int solve(const std::string &input) {
	std::set<Point> points;
	auto p = Point{0,0};
	auto p2 = Point{0,0};
	bool flag = false;
	points.insert(p);
	for (char c : input) {
		if (flag) {
			switch (c) {
				case 'v': p.y++; break;
				case '^': p.y--; break;
				case '<': p.x++; break;
				case '>': p.x--; break;
				default: break;
			}
			points.insert(p);
		} else {
			switch (c) {
				case 'v': p2.y++; break;
				case '^': p2.y--; break;
				case '<': p2.x++; break;
				case '>': p2.x--; break;
				default: break;
			}
			points.insert(p2);
		}
		flag = !flag;
	}

	return points.size();
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
		//{"t1.txt", 2},
		{"t2.txt", 3},
		{"t3.txt", 11}
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