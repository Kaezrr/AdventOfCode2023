#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <algorithm>

using ll = long long int;

static std::unordered_map<char, int> cards{ {'J', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, 
											{'6', 5}, {'7', 6}, {'8', 7}, {'9', 8},
											{'T', 9}, {'Q', 10}, {'K', 11}, {'A', 12} };


int getScore(std::unordered_map<char, int>& m, int max) {
	if (m['J'] < max) {
		return max + m['J'] - (static_cast<int>(m.size()) - 1);
	}

	int second_highest = 0;
	for (const auto& [k, v] : m) {
		if (k == 'J') continue;
		second_highest = std::max(second_highest, v);
	}
	return max + second_highest - (static_cast<int>(m.size()) - ((second_highest) ? 1 : 0));
}


bool compareType(const std::string_view h1, const std::string_view h2) {
	std::unordered_map<char, int> m1, m2;
	int max1 = 0;
	int	max2 = 0;

	for (int i{ 0 }; i < 5; ++i) {
		max1 = std::max(max1, ++m1[h1[i]]);
		max2 = std::max(max2, ++m2[h2[i]]);
	} 

	int score1{ getScore(m1, max1) };
	int score2{ getScore(m2, max2) };
	
	if (score1 != score2) return score1 < score2;

	for (int i{ 0 }; i < 5; i++) {
		if (h1[i] == h2[i]) continue;
		return cards[h1[i]] < cards[h2[i]];
	}

	return true;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream in{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	std::vector<std::pair<std::string, int>> hands;

	while (std::getline(in, line)) {
		int bid;
		std::string hand;
		std::stringstream ss{ line };
		ss >> hand >> bid;
		hands.emplace_back(std::pair{ hand, bid });
	}

	std::sort(hands.begin(), hands.end(), 
		[](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) 
		{ return compareType(a.first, b.first); });

	int score{ 0 };
	for (int i{ 1 }; i <= hands.size(); ++i) {
		score += hands[i-1].second * i;
	}
	std::cout << "Answer: " << score << '\n';

	return 0;
}
