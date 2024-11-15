#include <utils.h>

int solve(const std::string &input, int iterations) {
	Table<char> boards[] = {
		Table<char>(),
		Table<char>()
	};
	for (const auto& line : split(input, "\n")) {
		std::vector<char> row = std::vector(line.begin(), line.end());
		boards[0].push_back(row);
		boards[1].push_back(row);
	}

	int width = boards[0][0].size();
	int height = boards[0].size();
	int board_idx = 0;

	for (int i = 0; i < iterations; ++i) {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				int neighbors = 0;
				for (int rx = max(x-1, 0); rx < min(x+2, width); ++rx) {
					for (int ry = max(y-1, 0); ry < min(y+2, height); ++ry) {
						if (rx == x && ry == y) continue;

						if (boards[board_idx][ry][rx] == '#')
							++neighbors;
					}
				}
				if ((boards[board_idx][y][x] == '#' && neighbors == 2) || neighbors == 3) {
					boards[1-board_idx][y][x] = '#';
				} else {
					boards[1-board_idx][y][x] = '.';
				}
			}
		}
		board_idx = 1 - board_idx;
	}

	int count = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (boards[board_idx][y][x] == '#')
				++count;
		}
	}

	return count;
}

int main(int argc, char** argv) {
    auto runner = Runner<int, int>(solve, 2015, 18);
    runner.add_test_file("t1.txt", 15, 0);
    runner.add_test_file("t1.txt", 11, 1);
    runner.add_test_file("t1.txt", 8, 2);
    runner.add_test_file("t1.txt", 4, 3);
    runner.add_test_file("t1.txt", 4, 4);

    runner.add_input_file("i1.txt", 100);

    runner.run();
}