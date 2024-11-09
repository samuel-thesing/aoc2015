#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "07"

bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

bool isLowercase(char c) {
	return 'a' <= c && c <= 'z';
}

bool isUppercase(char c) {
	return 'A' <= c && c <= 'Z';
}

bool eval_wire(const std::string& wire, std::unordered_map<std::string, unsigned short>& values) {
	const auto [expression, target] = extract_data<std::string, std::string>(std::regex("(.*) -> (.*)"), wire);

	auto parts = split(expression, " ");

	std::string op;

	std::vector<unsigned short> inputs{};
	for (const std::string& part : parts) {
		if (isDigit(part[0])) {
			inputs.push_back((unsigned short)std::stoi(part));
		} else if (isLowercase(part[0])) {
			auto it = values.find(part);
			if (it == values.end())
				return false;

			inputs.push_back(it->second);
		} else if (isUppercase(part[0])) {
			op = part;
		}
	}

	unsigned short result = 0;

	if (op == "AND") {
		result = inputs[0] & inputs[1];
	} else if (op == "OR") {
		result = inputs[0] | inputs[1];
	} else if (op == "LSHIFT") {
		result = inputs[0] << inputs[1];
	} else if (op == "RSHIFT") {
		result = inputs[0] >> inputs[1];
	} else if (op == "NOT") {
		result = ~inputs[0];
	} else if (op == "NONE" || op.empty()) {
		result = inputs[0];
	}

	values.emplace(target, result);

	return true;
}

unsigned short solve(const std::string &input) {
	auto lines = split(input, "\n");
	std::unordered_map<std::string, unsigned short> values{};
	std::regex pattern("(.*) -> (.*)");
	std::queue<std::string> wires;
	for (const auto& line : lines) {
		if (!eval_wire(line, values)) {
			wires.push(line);
		} else {
			auto it = values.find("a");
			if (it != values.end()) {
				return it->second;
			}
		}
	}

	while (!wires.empty()) {
		std::string wire = wires.front();
		wires.pop();
		if (!eval_wire(wire, values)) {
			wires.push(wire);
		} else {
			auto it = values.find("a");
			if (it != values.end()) {
				return it->second;
			}
		}
	}

	for (const auto& [key, value] : values) {
		std::cout << key << ": " << value << std::endl;
	}

	return -1;
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
		{"t1.txt", 65079}
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