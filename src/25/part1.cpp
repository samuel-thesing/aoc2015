#include <utils.h>

uint64_t solve(const std::string &input) {
	const auto target_coord = split<int>(input, "\n", [](std::string s) {return std::stoi(s);});

	int target_diag = target_coord[0] + target_coord[1] - 1;
	int diag_idx = target_coord[1] - 1;
	int diag_off = (target_diag-1) * target_diag / 2;

	int target_idx = diag_off + diag_idx;

	uint64_t num = 20151125;

	for (int i = 0; i < target_idx; i++) {
		num *= 252533;
		num %= 33554393;
	}
	return num;
}

int main(int argc, char** argv) {
    auto runner = Runner<uint64_t>(solve, 2015, 25);

	runner.add_test_string("1\n1", 20151125);
	runner.add_test_string("2\n2", 21629792);
	runner.add_test_string("3\n4", 7981243);
	runner.add_test_string("6\n6", 27995004);

    runner.add_input_file("i1.txt");

    runner.run();
}