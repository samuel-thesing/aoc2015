#ifndef UTILS_H
#define UTILS_H

#include <regex>
#include <queue>

#include "io_utils.h"


std::string trim(std::string s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) {
		return !std::isspace(c);
	}));

	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c) {
		return !std::isspace(c);
	}).base(), s.end());

	return s;
}

std::vector<std::string> split(const std::string& s, const std::string& delim) {
	if (trim(s).empty()) {
		return {};
	}

	size_t lastDelim = 0;
	auto curDelim = s.find(delim, lastDelim);
	std::vector<std::string> parts{};

	while (curDelim != std::string::npos) {
		std::string part = s.substr(lastDelim, curDelim - lastDelim);
		parts.emplace_back(trim(part));
		lastDelim = curDelim + delim.size();
		curDelim = s.find(delim, lastDelim);
	}

	auto lastPart = s.substr(lastDelim);
	parts.emplace_back(trim(lastPart));

	return parts;
}

template<typename T>
std::vector<T> split(const std::string& s, const std::string& delim, std::function<T(std::string)> fn) {
	auto splitted = split(s, delim);
	auto result = std::vector<T>();
	result.reserve(splitted.size());
	for (auto str : splitted) {
		result.emplace_back(fn(str));
	}
	return result;
}

std::pair<std::string, std::string> split_once(const std::string& s, const std::string& delim) {
	auto idx = s.find(delim);
	if (idx == std::string::npos) {
		return {s, ""};
	}

	return {s.substr(0, idx), s.substr(idx + delim.size())};
}

std::string pad_left(const std::string& s, int len) {
	return std::string(std::max(len - s.length(), 0ull), ' ') + s;
}

std::string pad_right(const std::string& s, int len) {
	return s + std::string(std::max(len - s.length(), 0ull), ' ');
}

template<typename T, typename... Args> requires (std::is_same_v<T, Args...>)
T max(T arg, Args... args) {
	return max(arg, max(args));
}

template<typename T, typename U> requires (std::is_same_v<T, U>)
T max(T t, U u) {
	return t > u ? t : u;
}

template<typename T, typename... Args> requires (std::is_same_v<T, Args...>)
T min(T arg, Args... args) {
	return min(arg, min(args));
}

template<typename T, typename U> requires (std::is_same_v<T, U>)
T min(T t, U u) {
	return t < u ? t : u;
}



template<typename T>
T string_to_generic(std::string s) {
	Logger::critical("No implementation for generating this generic");
	return T();
}

template<>
std::string string_to_generic<std::string>(std::string s) {
	return s;
}

template<>
int string_to_generic<int>(std::string s) {
	return std::stoi(s);
}

template<>
long string_to_generic<long>(std::string s) {
	return std::stol(s);
}

template<>
double string_to_generic<double>(std::string s) {
	return std::stod(s);
}

template<>
char string_to_generic<char>(std::string s) {
	return s[0];
}


template<typename... Args, std::size_t... Indices>
std::tuple<Args...> make_tuple_from_match(const std::smatch& match, std::index_sequence<Indices...>) {
	return std::make_tuple<Args...>(string_to_generic<Args>(match[Indices + 1].str())...);
}

template<typename... Args>
std::tuple<Args...> extract_data(const std::regex& pattern, std::string s) {
	std::smatch match;
	if (!std::regex_match(s, match, pattern)) {
		Logger::critical("Failed to match regex for '{}'", s);
	}

	return make_tuple_from_match<Args...>(match, std::index_sequence_for<Args...>{});
}

bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

bool isLowercase(char c) {
	return 'a' <= c && c <= 'z';
}

bool isUppercase(char c) {
	return 'A' <= c && c <= 'Z';
}

#endif //UTILS_H
