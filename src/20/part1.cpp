#include <utils.h>

int solve(const std::string &input) {
	int target = std::stoi(input);
	target /= 10;

	std::vector<int> sums = std::vector(target, 0);
	for (int i = 1; i < target; i++) {
		for (int j = i; j < target; j += i) {
			sums[j] += i;
		}
	}

	for (int i = 1; i < target; i++) {
		if (sums[i] >= target) {
			return i;
		}
	}

	return 0;
}

int main(int argc, char** argv) {
    auto runner = Runner<int>(solve, 2015, 20);
    runner.add_test_string("40", 3);
    runner.add_test_string("70", 4);
    runner.add_test_string("60", 4);
    runner.add_test_string("150", 8);

    runner.add_input_file("i1.txt");

    runner.run();
}