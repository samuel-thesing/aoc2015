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

#endif //IO_UTILS_H
