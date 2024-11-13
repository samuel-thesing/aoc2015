#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "15"

typedef std::vector<std::vector<std::array<long, 5>>> PreCalcTable;

long recursive(const PreCalcTable& preCalcTable, long ingredient_idx, long spoons_used, std::vector<long>& spoons) {
	if (ingredient_idx == spoons.size()-1) {
		spoons[spoons.size()-1] = 100-spoons_used;
		int calories = 0;
		for (int j = 0; j < spoons.size(); j++) {
			calories += preCalcTable[j][spoons[j]][4];
		}
		if (calories != 500) {
			return 0;
		}

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

bool test(const std::string &filename, long expected) {
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
	std::vector<std::pair<std::string, long>> test_files = {
		{"t1.txt", 57600000}
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