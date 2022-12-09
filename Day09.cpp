#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <set>

namespace Day09 {

	struct Position {
		int x;
		int y;

		bool operator<(const Position& other) const
		{
			return y == other.y ? x < other.x : y < other.y;
		}

		Position& operator+=(const Position& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Position& operator+=(const int other) {
			x += other;
			y += other;
			return *this;
		}

		Position operator+(const Position& other) const {
			return { x + other.x, y + other.y };
		}

		Position operator+(const int other) const {
			return { x + other, y + other };
		}

		Position operator-(const Position& other) const {
			return { x - other.x, y - other.y };
		}

		Position operator-(const int other) const {
			return { x - other, y - other };
		}

		Position operator/(const int other) const {
			return { x / other, y / other };
		}

		Position& operator/=(const int other) {
			x /= other;
			y /= other;
			return *this;
		}
	};

	typedef enum direction_t { U = 0, R = 1, D = 2, L = 3, INVALID } Direction;

	const std::array<const Position, 4> off = {
		{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} }
	};

	Direction toDirection(char c) {
		switch (c) {
		case 'U': return U;
		case 'R': return R;
		case 'D': return D;
		case 'L': return L;
		}
		return INVALID;
	}

	// calculates distance between two Points, diagonal points are distance 1 apart
	int distance(const Position& p1, const Position& p2) {
		return std::max(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y));
	}

	// return true if moved else false
	bool move(const Position& H, Position& T) {
		if (distance(H, T) > 1) {
			// divide dist of H and T by 2 (2 is the norm of H-T)
			T = H - (H - T) / 2;
			return true;
		}
		else return false;
	}

	void makeMove(Position& H, Position& T, const Direction dir, int steps, std::set<Position>& visited) {
		for (int k = 0; k < steps; ++k) {
			H += off[dir];
			move(H, T);
			if (!visited.contains(T))
				visited.insert(T);
		}
	}

	void moveSnake(Position& H, std::array<Position, 9>& rope, const Direction dir, int steps, std::set<Position>& visited) {
		for (int k = 0; k < steps; ++k) {
			H += off[dir];
			Position last = H;
			for (Position& T : rope) {
				if (!move(last, T)) break;
				last = T;
			}
			if (!visited.contains(rope[8])) {
				std::cout << rope[8].x << ' ' << rope[8].y << std::endl;
				visited.insert(rope[8]);
			}
		}
	}

	void part1() {
		std::ifstream input("Day09.txt");
		int steps;
		Position H = { 0, 0 };
		Position T = { 0, 0 };
		std::set<Position> visited = { {0, 0} };

		std::string line;
		while (std::getline(input, line)) {
			steps = std::stoi(line.substr(2, line.size() - 2));
			makeMove(H, T, toDirection(line[0]), steps, visited);
		}
		std::cout << "elements: " << visited.size() << std::endl;
	}

	void part2() {
		std::ifstream input("Day09.txt");
		int steps;
		Position H = { 0, 0 };
		std::array<Position, 9> T = { {0, 0} };
		std::set<Position> visited = { {0, 0} };

		std::string line;
		while (std::getline(input, line)) {
			steps = std::stoi(line.substr(2, line.size() - 2));
			moveSnake(H, T, toDirection(line[0]), steps, visited);
		}
		std::cout << "elements: " << visited.size() << std::endl;
	}

	void main() {
		part2();
	}

}