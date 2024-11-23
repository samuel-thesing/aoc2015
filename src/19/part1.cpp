#include <utils.h>

int solve(const std::string &input) {
	std::unordered_set<std::string> molecules;

	std::regex pattern("(.+) => (.+)");

	const auto [replacements, start_molecule] = split_once(input, "\n\n");
	for (const auto& replacement : split_lines(replacements)) {
		const auto& [from, to] = extract_data<std::string, std::string>(pattern, replacement);
		for (size_t i : find_all_idx(start_molecule, from)) {
			std::string molecule_copy = start_molecule;
			molecule_copy.replace(i, from.size(), to);
			molecules.emplace(molecule_copy);
		}
	}

	return molecules.size();
}

int main(int argc, char** argv) {
    auto runner = Runner<int>(solve, 2015, 19);
    runner.add_test_file("t1.txt", 4);
    runner.add_test_file("t2.txt", 7);

    runner.add_input_file("i1.txt");

    runner.run();
}