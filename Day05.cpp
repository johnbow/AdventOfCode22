#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <deque>
#include <array>
#include <regex>

void part1() {
	std::ifstream input("Day05.txt");
	std::string line;

	std::regex moveMatcher("move ([0-9]+) from ([0-9]+) to ([0-9]+)");
	std::smatch matches;

	std::vector<std::deque<char>> queues;
	std::vector<std::stack<char>> stacks;

	while (std::getline(input, line)) {		// read crates
		if (line.empty())
			break;
		for (size_t i = 1, k = 0; i < line.size(); i += 4, ++k) {
			if (line[i] == ' ')
				continue;
			if (std::isdigit(line[i]))
				break;
			for (int j = k - queues.size(); j >= 0; --j)
				queues.emplace_back();		// push to right size
			queues[k].push_front(line[i]);
		}
	}
	for (const auto& queue : queues)		// convert queues to stacks
		stacks.emplace_back(queue);

	std::array<int, 3> arr;
	while (std::getline(input, line)) {		// execute moves
		std::regex_search(line, matches, moveMatcher);
		size_t amount = std::stoi(matches[1]);
		size_t from = std::stoi(matches[2]) - 1;
		size_t to = std::stoi(matches[3]) - 1;

		for (size_t i = 0; i < amount; ++i) {
			stacks[to].push(stacks[from].top());
			stacks[from].pop();
		}
	}
	for (const std::stack<char>& stack : stacks)
		std::cout << stack.top();
	std::cout << std::endl;
}

void part2() {
	std::ifstream input("Day05.txt");
	std::string line;

	std::regex moveMatcher("move ([0-9]+) from ([0-9]+) to ([0-9]+)");
	std::smatch matches;

	std::vector<std::deque<char>> queues;
	std::vector<std::stack<char>> stacks;

	while (std::getline(input, line)) {		// read crates
		if (line.empty())
			break;
		for (size_t i = 1, k = 0; i < line.size(); i += 4, ++k) {
			if (line[i] == ' ')
				continue;
			if (std::isdigit(line[i]))
				break;
			for (int j = k - queues.size(); j >= 0; --j)
				queues.emplace_back();		// push to right size
			queues[k].push_front(line[i]);
		}
	}
	for (const auto& queue : queues)		// convert queues to stacks
		stacks.emplace_back(queue);

	std::array<int, 3> arr;
	while (std::getline(input, line)) {		// execute moves
		std::regex_search(line, matches, moveMatcher);
		size_t amount = std::stoi(matches[1]);
		size_t from = std::stoi(matches[2]) - 1;
		size_t to = std::stoi(matches[3]) - 1;

		std::stack<char> temp;

		for (size_t i = 0; i < amount; ++i) {	// push to temporary stack
			temp.push(stacks[from].top());
			stacks[from].pop();
		}
		for (size_t i = 0; i < amount; ++i) {	// push from temporary stack
			stacks[to].push(temp.top());
			temp.pop();
		}
	}
	for (const std::stack<char>& stack : stacks)
		std::cout << stack.top();
	std::cout << std::endl;
}

void main() {
	part2();
}