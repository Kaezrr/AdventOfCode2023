#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <vector>
#include <cassert>
#include <array>
#include <unordered_map>

using ll = long long int;


std::unordered_map<std::string, std::string> workflow;

struct Part {
	int x, m, a, s;
	int getSum() const { return x + m + a + s; }
};


bool processExpression(const std::string& ex, const Part& p) {
	switch (ex[0]) {
	case 'x':
		return (ex[1] == '<') ? (p.x < std::stoi(ex.substr(2))) : (p.x > std::stoi(ex.substr(2)));
	case 'm':
		return (ex[1] == '<') ? (p.m < std::stoi(ex.substr(2))) : (p.m > std::stoi(ex.substr(2)));
	case 'a':
		return (ex[1] == '<') ? (p.a < std::stoi(ex.substr(2))) : (p.a > std::stoi(ex.substr(2)));
	case 's':
		return (ex[1] == '<') ? (p.s < std::stoi(ex.substr(2))) : (p.s > std::stoi(ex.substr(2)));
	}
	return false;
}


bool processPart(const std::string& wf, const Part& p) {
	if (wf == "A") return true;
	if (wf == "R") return false;

	std::string_view w = workflow[wf];
	std::string buffer = "";

	for (const auto& c : w) {
		if (c != ',') { buffer += c; continue; }

		auto col = buffer.find(':');
		if (processExpression(buffer.substr(0, col), p))
			return processPart(buffer.substr(col + 1), p);
		buffer.clear();
	}

	return processPart(buffer, p);
}


class RangePart {
private:
	std::array<std::pair<ll, ll>, 4> ranges;

public:
	RangePart() { ranges.fill({ 1, 4000 }); }

	void updateRange(const std::string& ex, bool pass) {
		int i{ -1 };
		switch (ex[0]) {
		case 'x': i = 0; break;
		case 'm': i = 1; break;
		case 'a': i = 2; break;
		case 's': i = 3; break;
		}
		assert(0 <= i && i <= 3);

		ll limit = std::stoll(ex.substr(2));
		if (pass) {
			ranges[i].first = (ex[1] == '<') ? ranges[i].first : std::max(limit + 1, ranges[i].first);
			ranges[i].second = (ex[1] == '<') ? std::min(limit - 1, ranges[i].second) : ranges[i].second;
		} else {
			ranges[i].first = (ex[1] == '<') ? std::max(limit, ranges[i].first) : ranges[i].first;
			ranges[i].second = (ex[1] == '<') ? ranges[i].second : std::min(limit, ranges[i].second);
		}
	}

	ll getCombinations() const {
		ll com{ 1 };
		for(const auto& c : ranges)
			com *= c.second - c.first + 1;
		return com;
	}
	
	bool validRange() {
		for (const auto& r : ranges) 
			if (r.first > r.second) return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& out, const RangePart& rp) {
		for (const auto& c : rp.ranges) {
			out << c.first << ' ' << c.second << '\n';
		}
		return out;
	}
};


ll getRange(const std::string& wf, RangePart& part) {
	if (wf == "A") return part.getCombinations();
	if (wf == "R" || !part.validRange()) return 0L;

	ll combo{ 0 };
	std::string_view w = workflow[wf];
	std::string buffer = "";

	for (const auto& c : w) {
		if (c != ',') { buffer += c; continue; }
		auto col = buffer.find(':');

		RangePart passed = part;
		passed.updateRange(buffer, true);
		combo += getRange(buffer.substr(col + 1), passed);

		part.updateRange(buffer, false);
		buffer.clear();
	}

	combo += getRange(buffer, part);
	return combo;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	std::vector<Part> parts;

	bool sw{ false };
	while (std::getline(file, line)) {
		if (line.empty()) {
			sw = true;
			continue;
		}

		if (sw) {
			auto x = line.find('x');
			auto m = line.find('m');
			auto a = line.find('a');
			auto s = line.find('s');

			parts.emplace_back(
				std::stoi(line.substr(x + 2, line.find(',', x) - x - 2)),
				std::stoi(line.substr(m + 2, line.find(',', m) - m - 2)),
				std::stoi(line.substr(a + 2, line.find(',', a) - a - 2)),
				std::stoi(line.substr(s + 2, line.find(',', s) - s - 2))
			);
		} else {
			auto div{ line.find('{') };
			workflow[line.substr(0, div)] = line.substr(div + 1, line.size() - div - 2);
		}
	}

	ll answer1{ 0 };
	for (const auto& part : parts) {
		if (!processPart("in", part)) continue;
		answer1 += part.getSum();
	}
	RangePart rp1;
	ll answer2{ getRange("in", rp1) };
	
	std::cout << "Part 1: " << answer1 << '\n';
	std::cout << "Part 2: " << answer2 << '\n';

	return 0;
}
