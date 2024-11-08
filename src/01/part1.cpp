#include <iostream>
#include <io_utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "01"


int solve(const std::string& input) {
	int sum = 0;
	for (auto c : input) {
		switch (c) {
			case '(': sum++; break;
			case ')': sum--; break;
			default: break;
		}
	}
	return sum;
}

int main(int argc, char** argv) {
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;

	std::string input = read_file("i1.txt");
	auto result = solve(input);
	std::cout << result << std::endl;
}