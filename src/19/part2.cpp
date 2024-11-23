#include <utils.h>

template <typename T>
using PairList = std::vector<std::pair<T, T>>;

typedef std::vector<std::string> Molecule;

int search_molecule(const PairList<std::string>& transformations, int step, const std::string& current) {
	if (current == "e") return step;

	for (const auto& [from, to] : transformations) {
		int n = 0;
		while (auto replaced = replace_nth(current, to, from, n)) {
			int result = search_molecule(transformations, step+1, replaced.value());
			if (result != -1) return result;
			n++;
		}
	}
	return -1;
}

int solve(const std::string &input) {
	std::vector<std::pair<std::string, std::string>> transformations;

	std::regex pattern("(.+) => (.+)");

	const auto [replacements, target_molecule] = split_once(input, "\n\n");
	for (const auto& replacement : split_lines(replacements)) {
		const auto& [from, to] = extract_data<std::string, std::string>(pattern, replacement);
		transformations.emplace_back(from, to);
	}

	int result = search_molecule(transformations, 0, target_molecule);

	return result;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 19);
	runner.add_test_file("t3.txt", 3);
	runner.add_test_file("t4.txt", 6);

	runner.add_input_file("i1.txt");

	runner.run();
}