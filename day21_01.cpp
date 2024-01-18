#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <unordered_set>
#include <cassert>

using ll = long long int;

struct PairHasher {
	std::size_t operator() (const std::pair<int, int>& pair) const {
		return ((std::hash<int>{} (pair.first) << 1) ^ (std::hash<int>{} (pair.second)));
	}
};


static std::vector<std::string> grid;

ll fill(int sr, int sc, int ss) {
	std::deque<std::array<int, 3>> nodes;
	std::vector<std::pair<int, int>> answer;
	std::unordered_set<std::pair<int, int>, PairHasher> seen;

	nodes.push_back({ sr, sc, ss });
	seen.insert({ sr, sc });

	while (!nodes.empty()) {
		auto [r, c, s] = nodes.front();
		nodes.pop_front();
			
		if (s % 2 == 0) answer.emplace_back(r, c);
		if (s == 0) continue;

		for (const auto& [nr, nc] : std::array<std::array<int, 2>, 4>{{ {r + 1, c}, {r - 1, c}, {r, c + 1}, {r, c - 1} }}) {
			if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[0].size() || grid[nr][nc] == '#' || seen.contains({nr, nc})) continue;
			seen.insert({ nr, nc });
			nodes.push_back({ nr, nc, s - 1 });
		}
	}

	return answer.size();
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "c:/users/invik/downloads/input.txt" };
	std::string line;

	int sr{0};
	int sc{0};
	while (std::getline(file, line)) {
		grid.emplace_back(line);
		if (line.contains("S")) {
			sr = static_cast<int>(grid.size() - 1);
			sc = static_cast<int>(line.find("S"));
		}
	}

	std::cout << "Part 1: " << fill(sr, sc, 64) << '\n';

	return 0;
}
