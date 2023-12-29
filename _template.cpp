#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using ll = long long int;


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << '\n';
	}

	return 0;
}
