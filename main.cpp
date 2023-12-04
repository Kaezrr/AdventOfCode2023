#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <sstream>
#include <cmath>
#include <unordered_set>

using ll = long long int;

int main() {
	std::ifstream input{ "C:/Users/invik/Downloads/input.txt" };
	std::vector<int> score_per_card{};
	std::string str;
	double answer{ 0 };

	while (std::getline(input, str)) {
		std::unordered_set<int> win, mine;
		const auto colon_pos{ str.find(":") };
		const auto pipe_pos{ str.find("|") };

		std::stringstream s1{ str.substr(colon_pos + 2, pipe_pos - (colon_pos + 2)) };
		std::stringstream s2{ str.substr(pipe_pos + 1) };
		
		while(!s1.eof()) { int n; s1 >> n; win.insert(n); }
		while(!s2.eof()) { int n; s2 >> n; mine.insert(n); }

		score_per_card.push_back(0);
		for (const auto& n : mine) {
			if (win.contains(n)) ++score_per_card.back();
		}
		answer += (score_per_card.back()) ? 1 << (score_per_card.back() - 1) : 0;
	}

	std::vector<int> cards(score_per_card.size(), 1);
	for (int i{ 0 }; i < cards.size(); ++i) {
		for (int j{ i + 1 }; j <= i + score_per_card[i]; ++j) {
			if (j > cards.size() - 1) break;
			cards[j] += cards[i];
		}
	}

	std::cout << "Part 1: " << answer << '\n';
	std::cout << "Part 2: " << std::accumulate(cards.begin(), cards.end(), 0) << '\n';

	return 0;
}