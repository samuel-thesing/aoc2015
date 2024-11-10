#include <iostream>

#include <io_utils.h>
#include <utils.h>
#include <Logger.h>

#define YEAR "2015"
#define DAY "09"

int traveling_salesman(const std::vector<std::string>& cities, std::vector<bool>& visited,
	std::unordered_map<std::string, std::unordered_map<std::string, int>>& adjMat, int curCityIdx) {

	int maxDist = 0;
	for (int i = 0; i < cities.size(); i++) {
		if (visited[i]) continue;

		visited[i] = true;
		int dist = adjMat[cities[curCityIdx]][cities[i]] + traveling_salesman(cities, visited, adjMat, i);
		if (dist > maxDist) {
			maxDist = dist;
		}
		visited[i] = false;

	}
	if (maxDist == 0) {
		return 0;
	}

	return maxDist;
}

int solve(const std::string &input) {
	std::unordered_map<std::string, std::unordered_map<std::string, int>> adjMat;
	auto lines = split(input, "\n");

	std::regex pattern("(.*) to (.*) = (.*)");
	for (const auto& line : lines) {
		const auto [city_a, city_b, dist] = extract_data<std::string, std::string, int>(pattern, line);
		if (adjMat.find(city_a) == adjMat.end()) {
			adjMat.emplace(city_a, std::unordered_map<std::string, int>());
		}

		if (adjMat.find(city_b) == adjMat.end()) {
			adjMat.emplace(city_b, std::unordered_map<std::string, int>());
		}

		adjMat[city_a].emplace(city_b, dist);
		adjMat[city_b].emplace(city_a, dist);
	}

	std::vector<std::string> cities;
	for (const auto& pair : adjMat) {
		cities.push_back(pair.first);
	}
	auto visited = std::vector<bool>(cities.size(), false);

	int maxDist = 0;
	for (int i = 0; i < cities.size(); i++) {
		if (visited[i]) continue;

		visited[i] = true;
		int dist = traveling_salesman(cities, visited, adjMat, i);
		if (dist > maxDist) {
			maxDist = dist;
		}
		visited[i] = false;
	}

	return maxDist;
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
		{"t1.txt", 982}
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