#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace Day02 {

	void part1() {
		const int n = 3;
		char self, opponent;
		int score = 0;
		std::vector<int> outcome = { 3, 0, 6 };
		std::ifstream ifs("Day02.txt");
		while (ifs >> opponent >> self) {
			const int a = self - ('X' - 1);
			const int b = opponent - ('A' - 4);
			const int select = (b - a) % n;
			score += a + outcome[select];
		}
		std::cout << score << std::endl;
	}

	void part2() {
		const int n = 3;
		char end, opponent;
		int score = 0;
		std::ifstream ifs("Day02.txt");
		while (ifs >> opponent >> end) {
			int mut = opponent + (end - 'Y');
			if (mut < 'A')
				mut += 3;
			else if (mut > 'C')
				mut -= 3;
			score += (mut - 'A' + 1) + 3 * (end - 'X');
		}
		std::cout << score << std::endl;
	}

	void main() {
		part2();
	}

}
