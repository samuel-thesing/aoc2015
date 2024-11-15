#include <utils.h>

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

unsigned short solve2(const std::string &input, std::unordered_map<std::string, unsigned short> &values) {
	auto lines = split(input, "\n");
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

unsigned solve(const std::string &input) {
	std::unordered_map<std::string, unsigned short> values{};
	solve2(input, values);
	auto result = values.find("a");
	values = std::unordered_map<std::string, unsigned short>();
	values.emplace("b", result->second);
	return solve2(input, values);
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 7);

	runner.add_input_file("i1.txt");

	runner.run();
}