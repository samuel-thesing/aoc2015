#include <utils.h>

int solve(const std::string &input) {
	auto lines = split(input, "\n");
	int nice_words = 0;
	for (const auto &line : lines) {
		bool double_pair = false;
		bool mirror_pair = false;
		for (int i = 0; i < line.size()-2; i++) {
			if (line[i] == line[i+2]) {
				mirror_pair = true;
			}

			auto pair = line.substr(i, 2);
			if (line.find(pair, i+2) != std::string::npos) {
				double_pair = true;
			}
		}

		if (mirror_pair && double_pair)
			nice_words++;
	}

	return nice_words;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 5);
	runner.add_test_string("qjhvhtzxzqqjkmpb", 1);
	runner.add_test_string("xxyxx", 1);
	runner.add_test_string("uurcxstgmygtbstg", 0);
	runner.add_test_string("ieodomkazucvgmuy", 0);

	runner.add_input_file("i1.txt");

	runner.run();
}