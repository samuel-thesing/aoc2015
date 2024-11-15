#include <utils.h>

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

int solve(const std::string &input, int race_length) {
	auto lines = split(input, "\n");

	std::regex pattern(".+ can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");

	std::vector<Reindeer> reindeers{};

	for (const auto &line : lines) {
		const auto& [speed, duration, rest] = extract_data<int, int, int>(pattern, line);

		reindeers.emplace_back(speed, duration, rest);
	}

	std::vector<int> points{};
	points.resize(reindeers.size(), 0);

	for (int i = 0; i < race_length; i++) {
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

int main(int argc, char** argv) {
	auto runner = Runner<int, int>(solve, 2015, 14);

	runner.add_test_file("t1.txt", 689, 1000);

	runner.add_input_file("i1.txt", 2503);

	runner.run();
}