#include <utils.h>

int solve(const std::string &input) {
	auto lines = split(input, "\n");

	auto sum = 0;

	for (const auto &line : lines) {
		auto sizes = split<int>(line, "x", [](std::string s) {
			return std::stoi(s);
		});
		std::vector sides = {
			sizes[0] * sizes[1],
			sizes[0] * sizes[2],
			sizes[1] * sizes[2]
		};

		auto smallest = std::ranges::min_element(sides);
		sum += *smallest;
		sum += 2* (sides[0] + sides[1] + sides[2]);
	}

	return sum;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 02);
	runner.add_test_string("2x3x4", 58);
	runner.add_test_string("1x1x10", 43);

	runner.add_input_file("i1.txt");

	runner.run();
}