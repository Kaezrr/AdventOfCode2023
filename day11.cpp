#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

static std::vector<std::vector<char>> galaxy{};
int findDistance(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int main() {
	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	while (std::getline(file, line)) {
		galaxy.emplace_back(line.begin(), line.end());
		if (!line.contains('#'))
			galaxy.emplace_back(line.begin(), line.end());
	}
	std::vector<int> col;
	for (int i{ 0 }; i < galaxy[0].size(); ++i) {
		bool filled{ false };
		for (const auto& v : galaxy) {
			if (v[i] == '.') continue;
			filled = true;
			break;
		}
		if (filled) continue;
		col.push_back(i);
	}
	for (int i{ 0 }; i < col.size(); ++i) {
		for (auto& v : galaxy) {
			v.insert(std::next(v.begin(), col[i] + i), '.');
		}
	}

	std::vector<std::pair<int, int>> coords;
	for (int i{ 0 }; i < galaxy.size(); ++i) {
		for (int j{ 0 }; j < galaxy[0].size(); ++j) {
			if (galaxy[i][j] == '.') continue;
			galaxy[i][j] = static_cast<char>('1' + coords.size());
			coords.emplace_back(i, j);
		}
	}
	
	int distance{ 0 };
	for (int i { 0 }; i < coords.size(); ++i) {
		for (int j{ i + 1 }; j < coords.size(); ++j) {
			distance += findDistance(coords[i], coords[j]);
		}
	}

	std::cout << "Part 1: " << distance << '\n';
	return 0;
}
