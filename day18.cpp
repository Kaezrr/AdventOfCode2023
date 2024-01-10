#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using ll = long long int;

ll shoelace(const std::vector<ll>& coordsX, const std::vector<ll>& coordsY) {
	ll area{ 0 };
	for (int i{ 0 }; i < coordsX.size() - 1; ++i) {
		area += (coordsX[i] * coordsY[i + 1]) - (coordsY[i] * coordsX[i + 1]);
	}
	return std::abs(area / 2);
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;

	ll x{ 0 };
	ll y{ 0 };
	ll x2{ 0 };
	ll y2{ 0 };

	ll boundaryPoints{ 0 };
	ll boundaryPoints2{ 0 };

	std::vector<ll> coordsX{ 0 };
	std::vector<ll> coordsY{ 0 };
	std::vector<ll> coordsX2{ 0 };
	std::vector<ll> coordsY2{ 0 };

	while (std::getline(file, line)) {
		std::stringstream ss{ line };
		char dir;
		int move;
		std::string hex;
		ss >> dir >> move >> hex;
		
		boundaryPoints += move;
		switch (dir) {
		case 'R':
			x += move;
			break;
		case 'L':
			x -= move;
			break;
		case 'D':
			y += move;
			break;
		case 'U':
			y -= move;
			break;
		}
		coordsX.push_back(x);
		coordsY.push_back(y);

		auto move2 = std::stoull(hex.substr(2, 5), nullptr, 16);
		auto dir2 = hex[hex.size() - 2];

		boundaryPoints2 += move2;
		switch (dir2) {
		case '0':
			x2 += move2;
			break;
		case '2':
			x2 -= move2;
			break;
		case '1':
			y2 += move2;
			break;
		case '3':
			y2 -= move2;
			break;
		}
		coordsX2.push_back(x2);
		coordsY2.push_back(y2);
	}
	auto answer1 = shoelace(coordsX, coordsY) + (boundaryPoints / 2) + 1;
	auto answer2 = shoelace(coordsX2, coordsY2) + (boundaryPoints2 / 2) + 1;

	std::cout << "Part 1: " << answer1 << '\n';
	std::cout << "Part 1: " << answer2 << '\n';

	return 0;
}
