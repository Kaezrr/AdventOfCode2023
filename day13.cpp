#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ll = long long int;

bool isHorizontal(int mir, const std::vector<std::string>& land) {
	int diff{ 0 };
	bool smudge{ false };
	while (mir - diff >= 0 && mir + diff + 1 <= land.size() - 1) {
		for (int i{ 0 }; i < land[mir].size(); ++i) {
			if (land[mir - diff][i] != land[mir + diff + 1][i]) {
				if (smudge) return false;
				smudge = true;
			}
		}
		++diff;
	}
	return smudge;
}


bool isVertical(int mir, const std::vector<std::string>& land) {
	int diff{ 0 };
	bool smudge{ false };
	while (mir - diff >= 0 && mir + diff + 1 <= land[0].size() - 1) {
		for (const auto& c : land)
			if (c[mir - diff] != c[mir + diff + 1]) {
				if (smudge) return false;
				smudge = true;
			}
		++diff;
	}

	return smudge;
}


bool smudgeCheck(std::string_view a, std::string_view b) {
	bool flag{ false };
	for (int i{ 0 }; i < a.size(); ++i) {
		if (a[i] == b[i]) continue;
		if (flag) return false;
		flag = true;
	}
	return true;
}


int calculate(const std::vector<std::string>& land) {
	for (int i{ 0 }; i < land.size()-1; ++i) {
		if (!smudgeCheck(land[i], land[i + 1])) continue;
		if (isHorizontal(i, land)) return (i + 1) * 100;
	}
	
	for (int i{ 0 }; i < land[0].size() - 1; ++i) {
		bool found{ true };
		bool smudge{ false };
		for (const auto& c : land) {
			if (c[i] == c[i + 1]) continue;
			if (smudge) {
				found = false;
				break;
			}
			smudge = true;
		}
		if (found && isVertical(i, land)) return i + 1;
	}

	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;
	
	int answer{ 0 };
	std::vector<std::string> map;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			map.push_back(line);
			continue;
		}
		answer += calculate(map);
		map.clear();
	}

	answer += calculate(map);
	std::cout << "Part 1: " << answer << '\n';

	return 0;
}
