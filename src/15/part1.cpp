#include <utils.h>

typedef Table<std::array<long, 5>> PreCalcTable;

long recursive(const PreCalcTable& preCalcTable, long ingredient_idx, long spoons_used, std::vector<long>& spoons) {
	if (ingredient_idx == spoons.size()-1) {
		spoons[spoons.size()-1] = 100-spoons_used;
		auto result = 1L;
		for (int i = 0; i < 4; ++i) {
			auto sum = 0L;
			for (int j = 0; j < spoons.size(); j++) {
				sum += preCalcTable[j][spoons[j]][i];
			}
			sum = max(0L, sum);
			result *= sum;
		}
		return result;
	}

	long max_res = 0;
	for (long i = 0; i <= 100 - spoons_used; i++) {
		spoons[ingredient_idx] = i;
		max_res = max(max_res, recursive(preCalcTable, ingredient_idx+1, spoons_used+i, spoons));
	}
	return max_res;
}

long solve(const std::string &input) {
	auto lines = split(input, "\n");
	std::vector<std::vector<long>> ingredients{};
	std::regex pattern(".+: capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)");
	for (const auto &line : lines) {
		const auto [cap, dur, fla, tex, cal] = extract_data<long, long, long, long, long>(pattern, line);
		ingredients.emplace_back(std::vector{cap, dur, fla, tex, cal});
	}
	PreCalcTable pre_calc{};
	for (long i = 0; i < ingredients.size(); ++i) {
		std::array<long, 5> counts{0, 0, 0, 0};
		pre_calc.emplace_back();
		pre_calc[i].emplace_back(counts);
		for (long j = 0; j <= 100; j++) {
			for (long k = 0; k < 5; k++) {
				counts[k] += ingredients[i][k];
			}
			pre_calc[i].emplace_back(counts);
		}
	}

	auto spoons = std::vector(ingredients.size(), 0L);
	long result = recursive(pre_calc, 0, 0, spoons);

	return result;
}

int main(int argc, char** argv) {
	auto runner = Runner<int>(solve, 2015, 15);

	runner.add_test_file("t1.txt", 62842880);

	runner.add_input_file("i1.txt");

	runner.run();
}