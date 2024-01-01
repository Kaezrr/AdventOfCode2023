#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <cstddef>
#include <unordered_map>

using ll = long long int;

enum Direction {
	right,
	left,
	down,
	up,
	unknown,
};


std::vector<std::string> plane;
std::unordered_map<std::string, std::vector<Direction>> energized;
constexpr std::array<std::pair<int, int>, 4> dir{ { {0, 1}, {0, -1}, {1, 0}, {-1, 0} } };


void simulateLight(int y, int x, Direction d) {
	while (y >= 0 && x >= 0 && y < plane.size() && x < plane[0].size()) {
		auto key = std::to_string(y) + ' ' + std::to_string(x);
		if (!energized.contains(key)) { energized[key] = { d }; }
		else if (std::find(energized[key].begin(), energized[key].end(), d) != energized[key].end()) { break; }
		else energized[key].push_back(d);

		switch (plane[y][x]) {
		case '-':
			if (d == up || d == down) {
				simulateLight(y, x + 1, right);
				simulateLight(y, x - 1, left);
				continue;
			}
			break;
		case '|':
			if (d == left || d == right) {
				simulateLight(y + 1, x, down);
				simulateLight(y - 1, x, up);
				continue;
			}
			break;
		case '/':
			if (d == right) { --y; d = up; }
			else if (d == left) { ++y; d = down; }
			else if (d == up) { ++x; d = right; }
			else if (d == down) { --x; d = left; }
			else
				break;
			continue;
		case '\\':
			if (d == right) { ++y; d = down; }
			else if (d == left) { --y; d = up; }
			else if (d == up) { --x; d = left; }
			else if (d == down) { ++x; d = right; }
			else
				break;
			continue;
		}
		y += dir[d].first;
		x += dir[d].second;
	}
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;
	
	while (std::getline(file, line)) {
		plane.push_back(line);
	}
	std::size_t answer{ 0 };
	int row{ static_cast<int>(plane[0].size()) };
	int col{ static_cast<int>(plane.size()) };

	for (int i{ 0 }; i < row; ++i) {
		simulateLight(0, i, Direction::down);
		answer = std::max(answer, energized.size());
		energized.clear();
	}
	for (int i{ 0 }; i < row; ++i) {
		simulateLight(col - 1, i, Direction::up);
		answer = std::max(answer, energized.size());
		energized.clear();
	}
	for (int i{ 0 }; i < col; ++i) {
		simulateLight(i, 0, Direction::right);
		answer = std::max(answer, energized.size());
		energized.clear();
	}
	for (int i{ 0 }; i < col; ++i) {
		simulateLight(i, row - 1, Direction::left);
		answer = std::max(answer, energized.size());
		energized.clear();
	}

	simulateLight(0, 0, Direction::right);

	std::cout << "Part 1: " << energized.size() << '\n';
	std::cout << "Part 2: " << answer << '\n';

	return 0;
}
