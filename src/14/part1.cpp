#include <utils.h>

int solve(const std::string &input, int race_length) {
	auto lines = split(input, "\n");

	std::regex pattern(".+ can fly (\\d+) km/s for (\\d+) seconds, but then must rest for (\\d+) seconds.");

	int max_dist = 0;

	for (const auto &line : lines) {
		const auto& [speed, duration, rest] = extract_data<int, int, int>(pattern, line);

		int distance = 0;
		int traveling = 0;
		for (int i = 0; i < race_length; i++) {
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

int main(int argc, char** argv) {
	auto runner = Runner<int, int>(solve, 2015, 14);

	runner.add_test_file("t1.txt", 1120, 1000);

	runner.add_input_file("i1.txt", 2503);

	runner.run();
}