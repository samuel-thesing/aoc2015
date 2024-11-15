#include <utils.h>

int solve(const std::string &input) {
	auto lines = split(input, "\n");
	int nice_words = 0;
	for (const auto &line : lines) {
		char prev_char = '\0';
		bool double_char = false;
		int num_vowels = 0;
		bool key_phrases = !(line.contains("ab")
			|| line.contains("cd")
			|| line.contains("pq")
			|| line.contains("xy"));
		for (const char c : line) {
			if (c == prev_char) {
				double_char = true;
			}

			switch (c) {
				case 'a':
				case 'e':
				case 'i':
				case 'o':
				case 'u':
					num_vowels++;
					break;
				default: break;
			}

			prev_char = c;
		}
		if (double_char && key_phrases && num_vowels > 2)
			nice_words++;
	}

	return nice_words;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 5);
	runner.add_test_string("ugknbfddgicrmopn", 1);
	runner.add_test_string("aaa", 1);
	runner.add_test_string("jchzalrnumimnmhp", 0);
	runner.add_test_string("haegwjzuvuyypxyu", 0);
	runner.add_test_string("dvszwmarrgswjxmb", 0);

	runner.add_input_file("i1.txt");

	runner.run();
}