#include <iostream>
#include <fstream>
#include <string>
#include <array>

using ll = long long int;

struct Node {
	std::string name;
	int focus;
	Node* next = nullptr;
};


int getHash(const std::string_view s) {
	int value{ 0 };
	for (const auto& c : s) {
		value += static_cast<int>(c);
		value *= 17;
		value %= 256;
	}
	return value;
}


void addNode(Node* head, const std::string& lens, int foc) {
	auto curr = head;
	while (curr->next != nullptr) {
		if (curr->name == lens) {
			curr->focus = foc;
			return;
		}
		curr = curr->next;
	}

	if (curr->name == lens) {
		curr->focus = foc;
		return;
	}

	curr->next = new Node{ lens, foc };
}


void removeNode(Node* head, const std::string& lens) {
	Node* prev = head;
	Node* curr = head->next;
	while (curr != nullptr && curr->name != lens) {
		prev = curr;
		curr = curr->next;
	}

	if (curr == nullptr) return;

	auto temp = curr;
	prev->next = curr->next;
	delete temp;
}


void processLens(const std::string& lens, std::array<Node*, 256>& map) {
	auto op = lens.contains('=') ? lens.find('=') : lens.find('-');
	auto pr = lens.substr(0, op);;
	auto hashValue = getHash(pr);

	if (lens[op] == '-') {
		if (map[hashValue] == nullptr) return;
		if (map[hashValue]->name == pr)
			map[hashValue] = map[hashValue]->next;
		else
			removeNode(map[hashValue], pr);
	} else {
		if (map[hashValue] == nullptr)
			map[hashValue] = new Node{ pr, std::stoi(lens.substr(op + 1)) };
		else
			addNode(map[hashValue], pr, std::stoi(lens.substr(op + 1)));
	}
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	std::ifstream file{ "C:/Users/invik/Downloads/input.txt" };
	std::string line;
	std::getline(file, line);

	std::array<Node*, 256> map{ nullptr };

	std::string lens{ "" };
	for (const auto& c : line) {
		if (c != ',') lens += c;
		else {
			processLens(lens, map);
			lens = "";
		}
	}
	processLens(lens, map);

	int answer{ 0 };
	for (int i{ 0 }; i < map.size(); ++i) {
		auto head = map[i];
		int pos{ 1 };
		while (head != nullptr) {
			answer += (i + 1) * head->focus * pos;
			pos += 1;
			head = head->next;
		}
	}

	std::cout << "Part 2: " << answer << '\n';

	return 0;
}
