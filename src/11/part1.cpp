#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "11"

bool check_pwd(const std::string& pwd) {
	if (pwd.find_first_of("iol") != std::string::npos) return false;

	int double_count = 0;
	for (int i = 0; i < pwd.size()-1; i++) {
		if (pwd[i] == pwd[i+1]) {
			double_count++;
			i++;
		}
	}
	if (double_count < 2) return false;

	for (int i = 0; i < pwd.size()-2; i++) {
		if (pwd[i+1] == pwd[i]+1 && pwd[i+2] == pwd[i]+2)
			return true;
	}
	return false;
}

std::string solve(const std::string &input) {
	std::string pwd = input;
	do {
		for (int i = pwd.size()-1; i >= 0; i--) {
			if (pwd[i] == 'z') {
				pwd[i] = 'a';
			} else {
				pwd[i]++;
				break;
			}
		}
	} while (!check_pwd(pwd));

	return pwd;
}

bool test(const std::string &filename, std::string expected) {
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
	std::vector<std::pair<std::string, std::string>> test_files = {
		{"t1.txt", "abcdffaa"},
		{"t2.txt", "ghjaabcc"}
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