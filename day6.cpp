#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using ull = unsigned long long int;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream in{ "C:/Users/invik/Downloads/input1.txt" };
	std::string line;

	std::vector <int> times;
	std::vector <int> records;

	std::getline(in, line);
	std::stringstream s1{ line.substr(line.find(':') + 1) };
	while (!s1.eof()) { int n; s1 >> n; times.push_back(n); }

	std::getline(in, line);
	std::stringstream s2{ line.substr(line.find(':') + 1) };
	while (!s2.eof()) { int n; s2 >> n; records.push_back(n); }

	int p1{ 1 };
	for (int i{ 0 }; i < times.size(); ++i) {
		int ways{ 0 };
		for (int t{ 1 }; t <= times[i]; ++t) {
			if (times[i] * t - (t * t) <= records[i]) continue;
			++ways;
		}
		p1 *= ways;
	}

	std::string time_string{};
	std::string record_string{};

	for (const auto& t : times) {
		time_string += std::to_string(t);
	}
	
	for (const auto& r : records) {
		record_string += std::to_string(r);
	}

	ull parsed_time{ std::stoull(time_string) };
	ull parsed_record{ std::stoull(record_string) };

	int p2{ 0 };
	for (ull t{ 0 }; t <= parsed_time; ++t) {
		if (parsed_time * t - (t * t) <= parsed_record) continue;
		++p2;
	}

	std::cout << "Part 1: " << p1 << '\n';
	std::cout << "Part 2: " << p2 << '\n';

	return 0;
}
