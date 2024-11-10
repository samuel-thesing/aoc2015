#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <math.h>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <filesystem>
#include <Logger.h>
#include <utils.h>
#include <set>

std::string read_file(std::string filename) {
	auto dir_name = std::filesystem::current_path().filename().string();
	auto cwd = std::filesystem::current_path() / "../../../" / "src" / dir_name;
	cwd = std::filesystem::canonical(cwd);
	auto file = std::ifstream(cwd / filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
		Logger::critical("Failed to open file '{}'. CWD: {}", filename, cwd.string());
    }

	std::stringstream contents;
	contents << file.rdbuf();
	return contents.str();
}

template<typename Key, typename Value>
void printAdjacencyMatrix(const std::unordered_map<Key, std::unordered_map<Key, Value>>& mat,
	std::function<std::string(Key)> keyFormatter, std::function<std::string(Value)> valueFormatter) {

	std::set<Key> keys;
	int max_key_len = 0;
	for (const auto& [key, row] : mat) {
		keys.emplace(key);
		max_key_len = std::max(max_key_len, (int)(keyFormatter(key).size()));
		for (const auto& [key2, _] : row) {
			keys.emplace(key2);
			max_key_len = std::max(max_key_len, (int)(keyFormatter(key2).size()));
		}
	}

	int keyCounter = 0;
	std::unordered_map<Key, int> keyIdx;
	for (const auto& key : keys) {
		keyIdx.emplace(key, keyCounter);
		keyCounter++;
	}

	std::vector<std::vector<std::string>> values;
	for (int i = 0; i < keyCounter; i++) {
		values.emplace_back(keyCounter, pad_left("-", max_key_len) + "  ");
	}

	for (const auto& [key, row] : mat) {
		const auto x = keyIdx.find(key);
		for (const auto& [key2, value] : row) {
			const auto y = keyIdx.find(key2);
			values[x->second][y->second] = pad_left(valueFormatter(value), max_key_len) + "  ";
		}
	}

	std::cout << pad_right("", max_key_len);
	for (const auto& key : keys) {
		std::cout << "  " << pad_right(std::string(key), max_key_len);
	}
	std::cout << std::endl;

	for (const auto& [key, row] : mat) {
		std::cout << pad_right(std::string(key), max_key_len) << "  ";
		const auto idx = keyIdx.find(key);
		for (const auto& value : values[idx->second]) {
			std::cout << value;
		}
		std::cout << std::endl;
	}
}

#endif //IO_UTILS_H
