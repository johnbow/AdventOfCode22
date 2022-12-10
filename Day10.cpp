#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>


namespace Day10 {

	void makeCycle(int& cycle, int& nextSignal, int x, int& signalStrengthSum) {
		cycle += 1;
		if (cycle >= nextSignal) {
			std::cout << nextSignal << " * " << x << " = " << nextSignal * x << std::endl;
			signalStrengthSum += x * nextSignal;
			nextSignal += 40;
		}
	}

	void drawPixel(int& cycle, int x, std::array<char, 40>& crt) {
		int col = cycle % 40;
		if (x - 1 <= col && col <= x + 1)
			crt[col] = '#';
		else
			crt[col] = '.';
		cycle += 1;
	}

	void printCRT(const std::array<std::array<char, 40>, 6>& crt) {
		for (size_t i = 0; i < 6; ++i) {
			for (size_t j = 0; j < 40; ++j) {
				std::cout << crt[i][j];
			}
			std::cout << std::endl;
		}
	}


	void part1() {
		std::ifstream input("Day10.txt");

		int x = 1;
		int cycle = 0;
		int nextSignal = 20;
		int sum = 0;

		std::string line;
		while (std::getline(input, line)) {
			const std::string command = line.substr(0, 4);
			if (command == "noop") {
				makeCycle(cycle, nextSignal, x, sum);
			}
			else if (command == "addx") {
				const int arg = std::stoi(line.substr(5, line.size() - 5));
				makeCycle(cycle, nextSignal, x, sum);
				makeCycle(cycle, nextSignal, x, sum);
				x += arg;
			}
			else
				std::cout << "Failed to read command." << std::endl;
		}
		std::cout << "Sum = " << sum << std::endl;
	}

	void part2() {
		std::ifstream input("Day10.txt");

		int x = 1;
		int cycle = 0;
		std::array<std::array<char, 40>, 6> crt;
		size_t currentRow = 0;

		std::string line;
		while (std::getline(input, line)) {
			const std::string command = line.substr(0, 4);
			if (command == "noop") {
				drawPixel(cycle, x, crt[currentRow]);
			}
			else if (command == "addx") {
				const int arg = std::stoi(line.substr(5, line.size() - 5));
				drawPixel(cycle, x, crt[currentRow]);
				drawPixel(cycle, x, crt[currentRow]);
				x += arg;
			}
			else
				std::cout << "Failed to read command." << std::endl;

			currentRow = cycle / 40;
		}
		printCRT(crt);
	}

	void main() {
		part2();
	}

}