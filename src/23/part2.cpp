#include <utils.h>

int solve(const std::string &input, int out_reg) {
	auto lines = split(input, "\n");
	std::array registers = {1, 0};
	int pc = 0;
	while (pc < lines.size()) {
		std::string line = lines.at(pc);
		char target = line.at(4) == 'a' ? 0 : 1;

		if (line.starts_with("hlf")) {
			registers[target] /= 2;
		} else if (line.starts_with("tpl")) {
			registers[target] *= 3;
		} else if (line.starts_with("inc")) {
			registers[target]++;
		} else if (line.starts_with("jmp")) {
			auto sign = line.at(4) == '+' ? 1 : -1;
			auto length = std::stoi(line.substr(5));
			pc += sign * length;
			continue;
		} else if (line.starts_with("jie")) {
			if (registers[target] % 2 == 0) {
				auto sign = line.at(7) == '+' ? 1 : -1;
				auto length = std::stoi(line.substr(8));
				pc += sign * length;
				continue;
			}
		} else if (line.starts_with("jio")) {
			if (registers[target] == 1) {
				auto sign = line.at(7) == '+' ? 1 : -1;
				auto length = std::stoi(line.substr(8));
				pc += sign * length;
				continue;
			}
		} else {
			Logger::critical("Invalid instruction '{}'", line);
		}

		pc++;
	}

	return registers[out_reg];
}

int main(int argc, char** argv) {
	auto runner = Runner<int, int>(solve, 2015, 23);
	runner.add_test_file("t1.txt", 7, 0);

	runner.add_input_file("i1.txt", 1);

	runner.run();
}