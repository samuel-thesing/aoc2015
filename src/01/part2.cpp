#include <utils.h>

int solve(const std::string& input) {
	int sum = 0;
	for (int i = 0; i < input.length(); i++) {
		switch (input[i]) {
			case '(': sum++; break;
			case ')': sum--; break;
			default: break;
		}
		if (sum < 0) return i+1;
	}
	return -1;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 01);
	runner.add_test_string(")", 1);
	runner.add_test_string("()())", 5);

	runner.add_input_file("i1.txt");

	runner.run();
}