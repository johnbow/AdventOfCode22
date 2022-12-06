#include <iostream>
#include <fstream>
#include <string>
#include <deque>

namespace Day06 {

	int findLastChar(std::deque<char>& queue, char c) {
		int i = queue.size() - 1;
		for (std::deque<char>::reverse_iterator it = queue.rbegin(); it != queue.rend(); ++it, --i) {
			if (*it == c)
				return i;
		}
		return -1;
	}

	void part1() {
		std::ifstream input("Day06.txt");
		std::deque<char> queue;
		char c;
		size_t i = 1;
		int duplicate = -1;

		for (; i < 4; ++i) {
			input >> c;
			int f = findLastChar(queue, c);
			if (f != -1)
				duplicate = f;
			queue.push_back(c);
		}

		while (input >> c) {
			int f = findLastChar(queue, c);
			if (f == -1 && duplicate < 0)
				break;
			else if (f != -1 && f > duplicate)
				duplicate = f;

			queue.push_back(c);
			queue.pop_front();
			--duplicate;
			++i;
		}
		for (char d : queue)
			std::cout << d << ' ';
		std::cout << c << std::endl;
		std::cout << i << std::endl;
	}

	void part2() {
		std::ifstream input("Day06.txt");
		std::deque<char> queue;
		char c;
		size_t n = 14;
		size_t i = 1;
		int duplicate = -1;

		for (; i < n; ++i) {
			input >> c;
			int f = findLastChar(queue, c);
			if (f != -1)
				duplicate = f;
			queue.push_back(c);
		}

		while (input >> c) {
			int f = findLastChar(queue, c);
			if (f == -1 && duplicate < 0)
				break;
			else if (f != -1 && f > duplicate)
				duplicate = f;

			queue.push_back(c);
			queue.pop_front();
			--duplicate;
			++i;
		}
		for (char d : queue)
			std::cout << d << ' ';
		std::cout << c << std::endl;
		std::cout << i << std::endl;
	}

	void main() {
		part2();
	}

}