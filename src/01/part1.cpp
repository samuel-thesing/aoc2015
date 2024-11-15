#include <utils.h>

int solve(const std::string& input) {
	int sum = 0;
	for (auto c : input) {
		switch (c) {
			case '(': sum++; break;
			case ')': sum--; break;
			default: break;
		}
	}
	return sum;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 01);
	runner.add_test_string("(())", 0);
	runner.add_test_string("()()", 0);
	runner.add_test_string("(((", 3);
	runner.add_test_string("(()(()(", 3);
	runner.add_test_string("))(((((", 3);
	runner.add_test_string("())", -1);
	runner.add_test_string("))(", -1);
	runner.add_test_string(")))", -3);
	runner.add_test_string(")())())", -3);

	runner.add_input_file("i1.txt");

	runner.run();
}