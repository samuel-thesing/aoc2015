#include <utils.h>

std::string solve(const std::string &input, int iterations) {
	std::string current = input;
	for (int i = 0; i < iterations; i++) {
		std::string next = "";
		int count = 0;
		char prev_c = '\0';
		for (char c : current) {
			if (c != prev_c) {
				if (count != 0) {
					next += std::to_string(count) + prev_c;
				}
				count = 1;
				prev_c = c;
			} else {
				count++;
			}
		}
		next += std::to_string(count) + prev_c;
		current = next;
	}

	return current;
}

int main(int argc, char** argv) {
	auto runner = Runner<std::string, int>(solve, 2015, 10);
	runner.set_result_transformation([](const std::string& s) {
		return std::to_string(s.size());
	});

	runner.add_test_string("1", "11", 1);
	runner.add_test_string("1", "21", 2);
	runner.add_test_string("1", "1211", 3);
	runner.add_test_string("11", "111221", 3);
	runner.add_test_string("1", "312211", 5);

	runner.add_input_file("i1.txt", 40);

	runner.run();
}