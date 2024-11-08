#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "02"

int solve(const std::string &input) {
	auto lines = split(input, "\n");

	auto sum = 0;

	for (const auto &line : lines) {
		auto sizes = split<int>(line, "x", [](std::string s) {
			return std::stoi(s);
		});

		auto biggest = std::ranges::max_element(sizes);
		sum += 2* (sizes[0] + sizes[1] + sizes[2]);
		sum -= *biggest * 2;
		sum += sizes[0] * sizes[1] * sizes[2];
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