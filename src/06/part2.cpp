#include <utils.h>

int solve(const std::string &input) {
	std::vector<int> lights = std::vector<int>(1000000, 0);
	int size = 1000;

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
					lights[offy+x] += 2;
				} else if (mode == 1) {
					lights[offy+x]++;
				} else {
					lights[offy+x] = max(0, lights[offy+x]-1);
				}
			}
		}
	}

	long total_brightness = 0;
	for (int i = 0; i < size*size; i++) {
		total_brightness += lights[i];
	}

	return total_brightness;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 6);
	runner.add_test_string("turn on 0,0 through 0,0", 1);
	runner.add_test_string("toggle 0,0 through 999,999", 2000000);

	runner.add_input_file("i1.txt");

	runner.run();
}