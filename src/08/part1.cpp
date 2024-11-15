#include <utils.h>

int solve(const std::string &input) {
	int sum = 0;
	auto lines = split(input, "\n");
	for (const auto& line : lines) {
		sum += 2;
		for (int i = 1; i < line.size()-1; i++) {
			if (line[i] == '\\') {
				if (line[i+1] == 'x') {
					sum += 3;
					i += 3;
				} else {
					sum++;
					i++;
				}
			}
		}
	}

	return sum;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 8);
	runner.add_test_string("\"\"", 2);
	runner.add_test_string("\"abc\"", 2);
	runner.add_test_string("\"aaa\\\"aaa\"", 3);
	runner.add_test_string("\"\\x27\"", 5);

	runner.add_input_file("i1.txt");

	runner.run();
}