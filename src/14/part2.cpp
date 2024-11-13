#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "14"

class Reindeer {
private:
	const int speed;
	const int duration;
	const int rest;

	int rest_timer = 0;
	int travel_counter = 0;

	int dist;

public:
	Reindeer(int speed, int duration, int rest)
		: speed(speed), duration(duration), rest(rest), dist(0) {}

	int tick() {
		if (rest_timer > 0) {
			rest_timer--;
			return dist;
		}

		travel_counter++;
		dist += speed;

		if (travel_counter >= duration) {
			rest_timer = rest;
			travel_counter = 0;
		}
		return dist;
	}

	int get_dist() const {
		return dist;
	}
};

int solve(const std::string &input) {
	auto lines = split(input, "\n");

	std::regex pattern(".+ can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");

	std::vector<Reindeer> reindeers{};

	for (const auto &line : lines) {
		const auto& [speed, duration, rest] = extract_data<int, int, int>(pattern, line);

		reindeers.emplace_back(speed, duration, rest);
	}

	std::vector<int> points{};
	points.resize(reindeers.size(), 0);

	for (int i = 0; i < 2503; i++) {
		std::vector<int> leaders{};
		int max_dist = 0;
		for (int j = 0; j < reindeers.size(); j++) {
			int dist = reindeers[j].tick();
			if (dist == max_dist) {
				leaders.push_back(j);
			}
			if (dist > max_dist) {
				max_dist = dist;
				leaders.clear();
				leaders.push_back(j);
			}
		}

		for (const auto leader : leaders) {
			points[leader]++;
		}
	}

	int max_points = 0;
	for (const auto point : points) {
		max_points = std::max(max_points, point);
	}

	return max_points;
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
		{"t1.txt", 1564}
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