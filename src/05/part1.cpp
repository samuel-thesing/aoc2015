#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "05"

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

bool test(const std::string &filename, int expected) {
	std::string input = read_file(filename);
	auto result = solve(input);
	if (result == expected) return true;

	Logger::error("{} failed. Expected {} but got {}", filename, expected, result);
	return false;
}

int main(int argc, char** argv) {
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;
	std::vector<std::pair<std::string, int>> test_files = {
		{"t1.txt", 2},
		{"t2.txt", 0}
	};
	bool test_failed = false;
	for (const auto& [test_file, expected_result] : test_files) {
		test_failed |= !test(test_file, expected_result);
	}
	if (test_failed) {
		Logger::critical("Aborting after failed tests");
	}
	Logger::info("All tests passed");

	std::string input = read_file("i1.txt");
	auto result = solve(input);
	std::cout << result << std::endl;
}