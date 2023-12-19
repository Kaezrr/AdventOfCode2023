#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using ll = long long int;

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

	ll p1{ 1 };
	for (int i{ 0 }; i < times.size(); ++i) {
		ll a = static_cast<ll>(0.5 * (-times[i] + std::sqrt(times[i] * times[i] - 4 * records[i])));
		ll b = static_cast<ll>(0.5 * (-times[i] - std::sqrt(times[i] * times[i] - 4 * records[i])));
		p1 *= a - b;
	}

	std::string time_string{};
	std::string record_string{};

	for (int i{ 0 }; i < times.size(); ++i) {
		time_string += std::to_string(times[i]);
		record_string += std::to_string(records[i]);
	}
	
	ll parsed_time{ std::stoll(time_string) };
	ll parsed_record{ std::stoll(record_string) };

	ll a = static_cast<ll>(0.5 * (-parsed_time + std::sqrt(parsed_time * parsed_time - 4 * parsed_record)));
	ll b = static_cast<ll>(0.5 * (-parsed_time - std::sqrt(parsed_time * parsed_time - 4 * parsed_record)));

	std::cout << "Part 1: " << p1 << '\n';
	std::cout << "Part 2: " << a - b << '\n';

	return 0;
}
