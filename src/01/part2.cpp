#include <iostream>
#include <io_utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "01"


int solve(const std::string& input) {
	int sum = 0;
	for (int i = 0; i < input.length(); i++) {
		switch (input[i]) {
			case '(': sum++; break;
			case ')': sum--; break;
			default: break;
		}
		if (sum < 0) return i+1;
	}
	return -1;
}

int main(int argc, char** argv) {
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;

	std::string input = read_file("i1.txt");
	auto result = solve(input);
	std::cout << result << std::endl;
}