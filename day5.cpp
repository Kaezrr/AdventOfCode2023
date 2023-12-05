#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using ll = long long int;

ll findNearestMatch(ll target, const std::vector<std::vector<ll>>& list) {
	for (const auto& n : list) {
		if (target >= n[1] && target <= n[1] + n[2] - 1) return n[0] + (target - n[1]);
	}
	return target;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream in{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	std::vector<ll> seeds;
	std::vector<std::vector<std::vector<ll>>> data;

	while (std::getline(in, line)) {
		if (line.empty()) continue;

		if (line.find(':') == 5) {
			ll n;
			std::stringstream str{ line.substr(line.find(':') + 1) };
			while (str >> n) seeds.push_back(n);
			continue;
		}

		if (line.back() == ':') { data.push_back({}); continue; }

		if (!seeds.empty()) {
			ll n1, n2, n3;
			std::stringstream str{ line };
			str >> n1 >> n2 >> n3;
			data.back().push_back({ n1, n2, n3 });
		}
	}


	for (const auto& d : data) 
		for (auto& seed : seeds) 
			seed = findNearestMatch(seed, d);

	std::cout << "Part 1: " << *std::min_element(seeds.begin(), seeds.end()) << '\n';

	return 0;
}
