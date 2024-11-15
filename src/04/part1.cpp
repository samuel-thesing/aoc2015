#include <utils.h>

#include "MD5.h"

int solve(const std::string &input) {
	MD5 md5;
	for (int i = 1; i < 10000000; i++) {
		if (md5(input + std::to_string(i)).starts_with("00000")) {
			return i;
		}
	}

	return 0;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 04);
	runner.add_test_string("abcdef", 609043);
	runner.add_test_string("pqrstuv", 1048970);

	runner.add_input_file("i1.txt");

	runner.run();
}