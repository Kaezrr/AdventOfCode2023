#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using ll = long long int;

static std::vector<std::vector<char>> galaxy{};
static ll findDistance(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return b.first - a.first + std::abs(a.second - b.second);
}

int main() {
	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	while (std::getline(file, line)) {
		galaxy.emplace_back(line.begin(), line.end());
	}

	std::vector<int> empty_rows;
	std::vector<int> empty_cols;
	int rc{ 0 }; 
	int cc{ 0 };
	for (const auto& v : galaxy) {
		bool empty = true;
		for (const auto& c : v) {
			if (c == '.') continue;
			empty = false;
			break;
		}
		if (empty) rc += 999999;
		empty_rows.push_back(rc);
	}

	for (int i{ 0 }; i < galaxy[0].size(); ++i) {
		bool empty = true;
		for (const auto& v : galaxy) {
			if (v[i] == '.') continue;
			empty = false;
			break;
		}
		if (empty) cc += 999999;
		empty_cols.push_back(cc);
	}

	std::vector<std::pair<int, int>> coords;
	for (int i{ 0 }; i < galaxy.size(); ++i) {
		for (int j{ 0 }; j < galaxy[0].size(); ++j) {
			if (galaxy[i][j] == '.') continue;
			coords.emplace_back(i + empty_rows[i], j + empty_cols[j]);
		}
	}
	
	ll distance{ 0 };
	for (int i { 0 }; i < coords.size(); ++i) {
		for (int j{ i + 1 }; j < coords.size(); ++j) {
			distance += findDistance(coords[i], coords[j]);
		}
	}
	std::cout << "Answer: " << distance << '\n';

	return 0;
}
