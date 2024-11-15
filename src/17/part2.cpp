#include <utils.h>

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

int main(int argc, char** argv) {
	auto runner = Runner<int, int>(solve, 2015, 17);

	runner.add_test_file("t1.txt", 3, 25);

	runner.add_input_file("i1.txt", 150);

	runner.run();
}