#include <utils.h>

std::string solve(const std::string &input) {
	std::unordered_map<std::string, int> map = {
		{"children", 3},
		{"cats", 7},
		{"samoyeds", 2},
		{"pomeranians", 3},
		{"akitas", 0},
		{"vizslas", 0},
		{"goldfish", 5},
		{"trees", 3},
		{"cars", 2},
		{"perfumes", 1}
	};

	std::regex pattern("(.+): (\\d+)");
	auto lines = split(input, "\n");


	for (const auto &line : lines) {
		auto [sue, parts] = split_once(line, ":");
		auto part_vec = split(parts, ", ");
		for (const auto& part : part_vec) {
			const auto [name, count] = extract_data<std::string, int>(pattern, part);
			auto ref_count = map[name];
			if (ref_count != count) {
				goto end_outer;
			}
		}

		return sue;

		end_outer:;
	}

	Logger::critical("No solution found");
}

int main(int argc, char** argv) {
	auto runner = Runner<std::string>(solve, 2015, 16);

	runner.add_input_file("i1.txt");

	runner.run();
}