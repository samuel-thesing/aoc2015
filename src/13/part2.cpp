#include <utils.h>

typedef std::unordered_map<std::string, std::unordered_map<std::string, int>> AdjMat;

int traveling_salesman_loop_recursive(AdjMat& adjMat, const std::vector<std::string>& persons, std::vector<bool>& visited, const int start, const int current) {
	int max_val = -1000000;
	int max_idx = -1;
	int free = 0;
	for (int i = 0; i < persons.size(); i++) {
		if (visited[i]) continue;

		free++;
		visited[i] = true;
		int result = adjMat[persons[current]][persons[i]] + traveling_salesman_loop_recursive(adjMat, persons, visited, start, i);
		if (result > max_val) {
			max_val = result;
			max_idx = i;
		}
		visited[i] = false;
	}
	if (free == 0) return 0;
	if (free == 1) {
		return max_val + adjMat[persons[max_idx]][persons[start]];
	}
	return max_val;
}

int traveling_salesman_loop(AdjMat& adjMat, const std::vector<std::string>& persons) {
	std::vector visited(adjMat.size(), false);
	visited[0] = true;
	int result = traveling_salesman_loop_recursive(adjMat, persons, visited, 0, 0);
	return result;
}

int solve(const std::string &input) {
	std::unordered_map<std::string, std::unordered_map<std::string, int>> adjMat;

	std::regex pattern("(.+) would (.+) (\\d+) happiness units by sitting next to (.+).");
	auto lines = split(input, "\n");
	for (const auto &line : lines) {
		const auto [person_a, signum, strength, person_b] = extract_data<std::string, std::string, int, std::string>(pattern, line);
		auto it = adjMat.find(person_a);
		if (it == adjMat.end()) {
			adjMat.emplace(person_a, std::unordered_map<std::string, int>());
		}

		int value = signum == "gain" ? strength : -strength;
		adjMat[person_a].emplace(person_b, value);
	}

	std::unordered_set<std::string> seenKeys;
	for (auto& [key, row] : adjMat) {
		seenKeys.insert(key);
		for (auto& [key2, value] : row) {
			if (seenKeys.contains(key2)) {
				continue;
			}
			const auto value2 = adjMat[key2][key];
			adjMat[key2][key] += value;
			adjMat[key][key2] += value2;
		}
	}

	adjMat.emplace("me", std::unordered_map<std::string, int>());
	for (const auto& person : seenKeys) {
		adjMat[person].emplace("me", 0);
		adjMat["me"].emplace(person, 0);
	}

	seenKeys.emplace("me");

	printAdjacencyMatrix<std::string, int>(adjMat, [](std::string s){return s;}, [](int i){return std::to_string(i);});

	return traveling_salesman_loop(adjMat, std::vector(seenKeys.begin(), seenKeys.end()));
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 13);

	runner.add_input_file("i1.txt");

	runner.run();
}