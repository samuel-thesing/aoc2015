#include <utils.h>

int solve(const std::string &input) {
	long sum = 0;
	std::string number;
	for (char i : input) {
		if (i == '-' || isDigit(i)) {
			number += i;
		} else if (!number.empty()) {
			sum += std::stoi(number);
			number = "";
		}
	}

	return sum;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 12);

	runner.add_test_string("[1,2,3]", 6);
	runner.add_test_string(R"({"a":2,"b":4})", 6);
	runner.add_test_string("[[[3]]]", 3);
	runner.add_test_string(R"({"a":{"b":4},"c":-1})", 3);
	runner.add_test_string(R"({"a":[-1,1]})", 0);
	runner.add_test_string(R"([-1,{"a":1}])", 0);
	runner.add_test_string("[]", 0);
	runner.add_test_string("{}", 0);

	runner.add_input_file("i1.txt");

	runner.run();
}