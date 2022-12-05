#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

namespace Day01 {

	void part1() {
		std::ifstream input("Day01.txt");
		std::string line;

		int maxVal = 0;
		int curVal = 0;
		while (std::getline(input, line)) {
			if (line.empty()) {
				curVal = 0;
				continue;
			}
			curVal += std::stoi(line);
			if (curVal > maxVal)
				maxVal = curVal;
		}
		std::cout << maxVal << std::endl;
	}

	void part2() {
		std::ifstream input("Day01.txt");
		std::string line;
		std::vector<int> values(4, 0);

		while (std::getline(input, line)) {
			if (line.empty()) {
				for (std::size_t i = 1; i < 4; ++i) {
					if (values[i - 1] > values[i])
						std::swap(values[i - 1], values[i]);
				}
				values[0] = 0;
			}
			else {
				values[0] += std::stoi(line);
			}
		}
		int sum = std::accumulate(std::next(values.begin()), values.end(), 0);
		std::cout << "Sum of 3 highest elements: " << sum << std::endl;
	}

	void main() {
		part2();
	}

}