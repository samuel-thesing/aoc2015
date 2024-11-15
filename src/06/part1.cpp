#include <utils.h>

int solve(const std::string &input) {
	std::array<bool, 1000000> lights{};
	int size = 1000;
	lights.fill(false);

	std::regex pattern("(turn off|turn on|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
	auto lines = split(input, "\n");
	for (const auto &line : lines) {
		const auto [mode_str, sx, sy, ex, ey] = extract_data<std::string, int, int, int, int>(pattern, line);
		int mode;
		if (mode_str == "turn on") {
			mode = 1;
		} else if (mode_str == "turn off") {
			mode = 0;
		} else {
			mode = 2;
		}

		for (int y = sy; y <= ey; y++) {
			int offy = y * size;
			for (int x = sx; x <= ex; x++) {
				if (mode == 2) {
					lights[offy+x] = !lights[offy+x];
				} else {
					lights[offy+x] = mode;
				}
			}
		}
	}

	int count = 0;
	for (int i = 0; i < size*size; i++) {
		count += lights[i];
	}

	return count;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 6);
	runner.add_test_string("turn on 0,0 through 999,999", 1000000);
	runner.add_test_string("toggle 0,0 through 999,0", 1000);
	runner.add_test_string("toggle 0,0 through 999,0\ntoggle 0,0 through 999,0", 0);
	runner.add_test_string("turn on 0,0 through 999,999\nturn off 499,499 through 500,500", 999996);

	runner.add_input_file("i1.txt");

	runner.run();
}