#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

namespace Day04 {

	typedef struct range_t {
		int lower;
		int upper;
	} range;

	inline bool range_contains(range r1, range r2) {
		return r1.lower >= r2.lower && r1.upper <= r2.upper;
	}

	inline bool range_overlaps(range r1, range r2) {
		return r1.lower <= r2.upper && r1.lower >= r2.lower;
	}

	void part1() {
		std::ifstream input("Day04.txt");
		std::string line;

		std::regex matcher("[0-9]+");
		std::string token1, token2;

		range r1, r2;
		int matches = 0;

		while (std::getline(input, line)) {
			std::size_t delim = line.find(',');
			token1 = line.substr(0, delim);
			token2 = line.substr(delim + 1, line.size());
			delim = token1.find('-');
			r1.lower = std::stoi(token1.substr(0, delim));
			r1.upper = std::stoi(token1.substr(delim + 1, token1.size()));
			delim = token2.find('-');
			r2.lower = std::stoi(token2.substr(0, delim));
			r2.upper = std::stoi(token2.substr(delim + 1, token2.size()));
			if (range_contains(r1, r2) || range_contains(r2, r1))
				++matches;
		}
		std::cout << "Matches: " << matches << std::endl;
	}

	void part2() {
		std::ifstream input("Day04.txt");
		std::string line;

		std::regex matcher("[0-9]+");
		std::string token1, token2;

		range r1, r2;
		int matches = 0;

		while (std::getline(input, line)) {
			std::size_t delim = line.find(',');
			token1 = line.substr(0, delim);
			token2 = line.substr(delim + 1, line.size());
			delim = token1.find('-');
			r1.lower = std::stoi(token1.substr(0, delim));
			r1.upper = std::stoi(token1.substr(delim + 1, token1.size()));
			delim = token2.find('-');
			r2.lower = std::stoi(token2.substr(0, delim));
			r2.upper = std::stoi(token2.substr(delim + 1, token2.size()));
			if (range_overlaps(r1, r2) || range_overlaps(r2, r1))
				++matches;
		}
		std::cout << "Matches: " << matches << std::endl;
	}

	void main() {
		part2();
	}

}