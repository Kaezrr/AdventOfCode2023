#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using ll = long long int;
using ull = unsigned long long int;

struct Module;

enum Type {
	broadcaster,
	flip,
	conjunction,
};

struct Transmission {
	std::string from;
	bool pulse;
	std::string to;
};

std::unordered_map<std::string, Module> moduleList;
std::queue<Transmission> orders;

struct Module {
	std::string name;
	Type type;
	std::vector<std::string> out;
	bool on{ false };
	std::unordered_map<std::string, bool> track;

	Module() = delete;

	Module(const std::string& n, Type t, const std::string& outStr) : name{n}, type{t} {
		std::string buffer = "";
		for (const auto& c : outStr) {
			if (c == ' ') { continue; }
			if (c != ',') { buffer += c; continue; }

			out.push_back(buffer);
			buffer.clear();
		}
		out.push_back(buffer);
	}

	void processModule(const std::string& from, bool pulse) {
		switch (type) {
		case broadcaster: processBroadcast(pulse); break;
		case flip: processFlip(pulse); break;
		case conjunction: processConjunction(from, pulse); break;
		}
	}

private:
	void processBroadcast(bool pulse) const {
		for (const auto& m : out) orders.emplace(name, pulse, m);
	}
	
	void processFlip(bool pulse) {
		if (pulse) return;
		on = !on;
		for (const auto& m : out) orders.emplace(name, on, m);
	}

	void processConjunction(const std::string& from, bool pulse) {
		track[from] = pulse;
		bool p = std::all_of(track.begin(), track.end(), [](const auto& p) {return p.second == true; });
		for (const auto& m : out) orders.emplace(name, !p, m);
	}
};


void processTransmission(const Transmission& tr) {
	if (!moduleList.contains(tr.to)) return;
	moduleList.at(tr.to).processModule(tr.from, tr.pulse);
}


ll pressButtonUntilX(const std::string& target, bool p) {
	ll count{ 0 };
	int xPulse{ 0 };
	while (xPulse != 1) {
		orders.emplace("button", false, "broadcaster");
		while (!orders.empty()) {
			xPulse += (orders.front().from == target && orders.front().pulse == p) ? 1 : 0;
			processTransmission(orders.front());
			orders.pop();
		}
		++count;
	}
	return count;
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	while (std::getline(file, line)) {
		Type t = broadcaster;
		switch (line[0]) {
		case '%': t = flip; break;
		case '&': t = conjunction; break;
		}

		auto m = line.find("->");
		auto name = (t == broadcaster) ? line.substr(0, m - 1) : line.substr(1, m - 2);
		moduleList.insert({ name, Module{ name, t, line.substr(m + 3) } });
	}

	for (const auto& [k, v] : moduleList) {
		for (const auto& s : v.out) {
			if (!moduleList.contains(s) || moduleList.at(s).type != conjunction) continue;
			moduleList.at(s).track[k] = false;
		}
	}

	// Use pressButtonUntilX function on the different modules that conjunction module on rx depends on to get the number of button presses they cycle on.

	constexpr ull answer = 3889ull * 3767ull * 3779ull * 4057ull;
	std::cout << "Part 2: " << answer << '\n';


	return 0;
}
