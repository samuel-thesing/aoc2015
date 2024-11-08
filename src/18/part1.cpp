#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "18"

int solve(const std::string &input) {

	return 0;
}

int main(int argc, char** argv) {
	Logger::init();
	std::cout << "Advent of Code " << YEAR << " Day " << DAY << std::endl
		<< "-------------------------------------------------------------" << std::endl;

	std::string input = read_file("i1.txt");
	auto result = solve(input);
	std::cout << result << std::endl;
}