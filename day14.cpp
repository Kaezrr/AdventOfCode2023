#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using ll = long long int;


void shiftNorth(std::vector<std::string>& platform) {
	for (int i{ 0 }; i < platform[0].size(); ++i) {
		int rock{ 0 };
		int wallPos{ -1 };
		for (int j{ 0 }; j < platform.size(); ++j) {
			if (platform[j][i] == '.') continue;
			if (platform[j][i] == 'O') { platform[j][i] = '.'; ++rock; continue; }
			while (rock > 0) { platform[++wallPos][i] = 'O'; --rock; }
			wallPos = j;
		}
		while (rock > 0) { platform[++wallPos][i] = 'O'; --rock; }
	}
}


void shiftSouth(std::vector<std::string>& platform) {
	for (int i{ 0 }; i < platform[0].size(); ++i) {
		int rock{ 0 };
		auto wallPos{ platform.size() };
		for (int j{ static_cast<int>(platform.size() - 1) }; j >= 0; --j) {
			if (platform[j][i] == '.') continue;
			if (platform[j][i] == 'O') { platform[j][i] = '.'; ++rock; continue; }
			while (rock > 0) { platform[--wallPos][i] = 'O'; --rock; }
			wallPos = j;
		}
		while (rock > 0) { platform[--wallPos][i] = 'O'; --rock; }
	}
}


void shiftWest(std::vector<std::string>& platform) {
	for (auto& s : platform) {
		int rock{ 0 };
		int wallPos{ -1 };
		for (int i{ 0 }; i < s.size(); ++i) {
			if (s[i] == '.') continue;
			if (s[i] == 'O') { s[i] = '.'; ++rock; continue; }
			while (rock > 0) { s[++wallPos] = 'O'; --rock; }
			wallPos = i;
		}
		while (rock > 0) { s[++wallPos] = 'O'; --rock; }
	}
}

void shiftEast(std::vector<std::string>& platform) {
	for (auto& s : platform) {
		int rock{ 0 };
		auto wallPos{ s.size() };
		for (int i{ static_cast<int>(s.size() - 1) }; i >= 0; --i) {
			if (s[i] == '.') continue;
			if (s[i] == 'O') { s[i] = '.'; ++rock; continue; }
			while (rock > 0) { s[--wallPos] = 'O'; --rock; }
			wallPos = i;
		}
		while (rock > 0) { s[--wallPos] = 'O'; --rock; }
	}
}


void shiftCycle(std::vector<std::string>& platform) {
	shiftNorth(platform);
	shiftWest(platform);
	shiftSouth(platform);
	shiftEast(platform);
}


int calculateWeight(std::vector<std::string>& platform) {
	int answer{ 0 };
	for (int i{ 0 }; i < platform.size(); ++i) {
		answer += static_cast<int>(std::count(platform[i].begin(), platform[i].end(), 'O') * (platform.size() - i));
	}
	return answer;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;
	
	std::vector<std::string> platform;
	while (std::getline(file, line)) {
		platform.emplace_back(line);
	}

	std::unordered_map<std::string, std::pair<int, int>> map;

	int i{ 1 };
	int loopStart;
	while(true) {
		shiftCycle(platform);
		std::string key{ "" };
		for (const auto& c : platform) { key += " " + c; }
		if (map.contains(key)) { loopStart = map[key].first; break; }
		map[key] = std::pair{ i, calculateWeight(platform) };
		++i;
	} 

	int loopIndex{ (1000000000 - loopStart) % (static_cast<int>(map.size()) - loopStart + 1) + loopStart};
	int answer{ 0 };
	for (const auto& [k, v] : map) {
		if (v.first != loopIndex) continue;
		answer = v.second;
		break;
	}
	std::cout << "Part 2: " << answer << '\n';

	return 0;
}
