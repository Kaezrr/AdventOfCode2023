#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using ll = long long int;
std::unordered_map<std::string, ll> cache;

ll possibleWays(const std::string& springs, const std::vector<int>& pattern) {
	if (springs == "") return pattern.empty() ? 1 : 0;
	if (pattern.empty()) return springs.contains('#') ? 0 : 1;

	auto key{ springs };
	for (const auto& p : pattern) key += ' ' + std::to_string(p);
	if (cache.contains(key)) return cache[key];

	ll result = 0;
	if (springs[0] != '#') result += possibleWays(springs.substr(1), pattern);
	if (springs[0] != '.') {
		if (pattern[0] <= springs.size() && !springs.substr(0, pattern[0]).contains('.') &&
			(pattern[0] == springs.size() || springs[pattern[0]] != '#'))
			result += possibleWays((pattern[0] == springs.size())? "" : springs.substr(pattern[0] + 1),
				std::vector(std::next(pattern.begin(), 1), pattern.end()));
	}

	cache[key] = result;
	return result;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	ll answer1{ 0 };
	ll answer2{ 0 };
	while (std::getline(file, line)) {
		auto unfoldedSprings{ line.substr(0, line.find(' ')) };
		auto unfoldedConfig{ line.substr(line.find(' ') + 1) };
		auto foldedSpring{ unfoldedSprings };
		auto foldedConfig{ unfoldedConfig };
		for (int i{ 0 }; i < 4; ++i) {
			unfoldedSprings += '?' + foldedSpring;
			unfoldedConfig += ',' + foldedConfig;
		}

		std::stringstream ss1{ foldedConfig };
		std::stringstream ss2{ unfoldedConfig };
		std::vector<int> patternFolded;
		std::vector<int> patternUnfolded;
		while (std::getline(ss1, line, ','))
			patternFolded.push_back(std::stoi(line));
		while (std::getline(ss2, line, ','))
			patternUnfolded.push_back(std::stoi(line));

		answer1 += possibleWays(foldedSpring, patternFolded);
		answer2 += possibleWays(unfoldedSprings, patternUnfolded);
	}

	std::cout << "Part 1: " << answer1 << '\n';
	std::cout << "Part 2: " << answer2 << '\n';
	return 0;
}
