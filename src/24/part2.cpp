#include <utils.h>

std::optional<std::pair<uint64_t, uint64_t>> search_tree(const uint64_t target, const std::vector<uint64_t>& packages,
	uint64_t idx = 0, uint64_t sum = 0, uint64_t count = 0, uint64_t qe = 1, int min_count = std::numeric_limits<int>::max()) {
	if (idx >= packages.size() || count >= min_count) return std::nullopt;


	std::pair<uint64_t, uint64_t> result = std::make_pair(std::numeric_limits<uint64_t>::max(), std::numeric_limits<uint64_t>::max());
	for (uint64_t i = idx; i < packages.size(); i++) {
		if (sum + packages[i] > target) {
			continue;
		}

		if (sum + packages[i] == target) {
			if (qe * packages[i] < result.second)
				result = {count+1, qe * packages[i]};
			continue;
		}

		if (result.first != std::numeric_limits<uint64_t>::max()) continue;
		// sum + packages[i] < target
		auto deep_result = search_tree(target, packages, i+1, sum + packages[i], count+1, qe * packages[i]);
		if (!deep_result) continue;
		if (deep_result->first < result.first || (deep_result->first == result.first && deep_result->second < result.second, result.first)) {
			result = deep_result.value();
		}
	}
	auto deep_result = search_tree(target, packages, idx+1, sum, count, qe, result.first);
	if (deep_result && (deep_result->first < result.first || (deep_result->first == result.first && deep_result->second < result.second))) {
		result = deep_result.value();
	}

	return result;
}

uint64_t solve(const std::string &input) {
	std::vector<uint64_t> packages = split<uint64_t>(input, "\n", [](std::string s){return std::stoll(s);});
	uint64_t target = sum(packages) / 4;

	std::sort(packages.begin(), packages.end(), std::greater());

	auto result = search_tree(target, packages);
	if (!result) return -1;
	return result->second;
}

int main(int argc, char** argv) {
	auto runner = Runner<uint64_t>(solve, 2015, 24);
	runner.add_test_file("t1.txt", 44);

	runner.add_input_file("i1.txt");

	runner.run();
}