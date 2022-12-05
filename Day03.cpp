#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

namespace Day03 {

	int priority(char c) {
		if (c >= 'a' && c <= 'z')
			return c - 'a' + 1;
		else
			return c - 'A' + 27;
	}

	void part1() {
		std::ifstream input("Day03.txt");
		std::set<char> chrs;
		std::string line;

		int sum = 0;
		while (std::getline(input, line)) {
			chrs.clear();
			int i;
			for (i = 0; i < line.size() / 2; ++i)
				chrs.insert(line[i]);
			for (; i < line.size(); ++i)
				if (chrs.contains(line[i]))
					break;
			for (const char c : chrs)
				std::cout << c << " ";
			std::cout << std::endl;
			std::cout << line[i] << " " << priority(line[i]) << std::endl;
			sum += priority(line[i]);

		}
		std::cout << sum << std::endl;
	}

	void part2() {
		std::ifstream input("Day03.txt");
		std::vector<std::set<char>> chrs(2);
		std::string line;

		int n = 0;
		int sum = 0;
		while (std::getline(input, line)) {
			int k = n % 3;
			int i = 0;
			if (k != 2) {
				for (; i < line.size(); ++i)
					chrs[k].insert(line[i]);
			}
			else {
				for (; i < line.size(); ++i) {
					if (chrs[0].contains(line[i]) && chrs[1].contains(line[i]))
						break;
				}
				sum += priority(line[i]);
				for (auto& chr : chrs)
					chr.clear();
			}
			++n;
		}
		std::cout << sum << std::endl;
	}

	void main() {
		part2();
	}

}
