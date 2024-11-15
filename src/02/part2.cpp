#include <utils.h>

int solve(const std::string &input) {
	auto lines = split(input, "\n");

	auto sum = 0;

	for (const auto &line : lines) {
		auto sizes = split<int>(line, "x", [](std::string s) {
			return std::stoi(s);
		});

		auto biggest = std::ranges::max_element(sizes);
		sum += 2* (sizes[0] + sizes[1] + sizes[2]);
		sum -= *biggest * 2;
		sum += sizes[0] * sizes[1] * sizes[2];
	}

	return sum;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 02);
	runner.add_test_string("2x3x4", 34);
	runner.add_test_string("1x1x10", 14);

	runner.add_input_file("i1.txt");

	runner.run();
}