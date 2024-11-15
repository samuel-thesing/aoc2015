#include <utils.h>

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

int main(int argc, char** argv) {
	auto runner = Runner<int, int>(solve, 2015, 17);

	runner.add_test_file("t1.txt", 4, 25);

	runner.add_input_file("i1.txt", 150);

	runner.run();
}