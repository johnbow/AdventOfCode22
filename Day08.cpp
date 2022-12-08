#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <stdio.h>

namespace Day08 {

	enum Vis { UP, RIGHT, DOWN, LEFT, VISIBLE };

	namespace Visibility {
		const int BLOCKED = 10;
		const int CLEAR = -1;
	}

	void fillTrees(std::vector<std::vector<int>>& treemap, std::ifstream& input) {
		size_t i = 0;
		std::string line;
		while (std::getline(input, line)) {
			treemap.emplace_back();
			for (char c : line)
				treemap[i].push_back(c - '0');
			++i;
		}
	}

	void fillVisibility(std::vector<std::vector<std::array<int, 5>>>& vis, size_t rows, size_t cols) {
		std::array<int, 5> defaultVis = { false, Visibility::BLOCKED, Visibility::BLOCKED, Visibility::BLOCKED, Visibility::BLOCKED };
		for (size_t i = 0; i < rows; ++i) {
			vis.emplace_back(cols, defaultVis);
			for (size_t j = 0; j < cols; ++j) {
				bool horizontal = true;
				bool vertical = true;
				if (i == 0)
					vis[i][j][UP] = Visibility::CLEAR;
				else if (i == rows - 1)
					vis[i][j][DOWN] = Visibility::CLEAR;
				else
					vertical = false;
				if (j == 0)
					vis[i][j][LEFT] = Visibility::CLEAR;
				else if (j == cols - 1)
					vis[i][j][RIGHT] = Visibility::CLEAR;
				else
					horizontal = false;
				vis[i][j][VISIBLE] = horizontal || vertical;
			}
		}
	}

	void fillVisibilityZero(std::vector<std::vector<std::array<int, 5>>>& vis, size_t size) {
		std::array<int, 5> defaultVis = { 0, 0, 0, 0, true };
		for (size_t i = 0; i < size; ++i) {
			vis.emplace_back(size, defaultVis);
		}
	}

	void calculateVisibilities(const std::vector<std::vector<int>>& treemap, std::vector<std::vector<std::array<int, 5>>>& vis) {
		const int size = treemap.size();

		const std::array<std::array<int, 2>, 4> off = { {
			{{-1, 0}}, {{0, 1}}, {{1, 0}}, {{0, -1}}
		} };

		const std::array<int, 5> start = { 1, 0, size - 2, 0, 1 };
		const std::array<int, 5> incr = { 1, 1, -1, 1, 1 };

		for (int dir = 0; dir < 4; ++dir) {
			for (int i = start[dir]; i >= 0 && i < size; i += incr[dir]) {
				for (int j = start[dir + 1]; j >= 0 && j < size; j += incr[dir + 1]) {
					vis[i][j][dir] = std::max(vis[i + off[dir][0]][j + off[dir][1]][dir], treemap[i + off[dir][0]][j + off[dir][1]]);
					vis[i][j][VISIBLE] = vis[i][j][VISIBLE] || vis[i][j][dir] < treemap[i][j];
				}
			}
		}
	}

	void calculateViewLengths(const std::vector<std::vector<int>>& treemap, std::vector<std::vector<std::array<int, 5>>>& vis) {
		const int size = treemap.size();

		const std::array<std::array<int, 2>, 4> off = { {
			{{-1, 0}}, {{0, 1}}, {{1, 0}}, {{0, -1}}
		} };

		for (int i = 1; i < size - 1; ++i) {
			for (int j = 1; j < size - 1; ++j) {
				for (int dir = 0; dir < 4; ++dir) {
					int x = j + off[dir][1];
					int y = i + off[dir][0];
					vis[i][j][dir] = 1;
					for (; x >= 1 && x < size - 1 && y >= 1 && y < size - 1; x += off[dir][1], y += off[dir][0]) {
						if (treemap[y][x] < treemap[i][j])
							++vis[i][j][dir];
						else break;
					}
				}
			}
		}
	}

	int calculateScenicScores(std::vector<std::vector<std::array<int, 5>>>& vis) {
		// scenic score is stored in vis[i][j][VISIBLE]. returns max scenic score
		int max = 0;
		for (auto& row : vis)
			for (auto& col : row) {
				col[VISIBLE] = col[UP] * col[RIGHT] * col[DOWN] * col[LEFT];
				if (col[VISIBLE] > max)
					max = col[VISIBLE];
			}
		return max;
	}

	void printVisibilities(const std::vector<std::vector<std::array<int, 5>>>& vis) {
		for (const auto& row : vis) {
			for (const auto& col : row)
				printf("%2d ", col[VISIBLE]);
			std::cout << std::endl;
		}
	}

	size_t countVisibilities(const std::vector<std::vector<std::array<int, 5>>>& vis) {
		size_t result = 0;
		for (const auto& row : vis) {
			for (const auto& col : row)
				if (col[VISIBLE])
					++result;
		}
		return result;
	}

	void part1() {
		std::ifstream input("Day08test.txt");
		std::vector<std::vector<int>> treemap;
		std::vector<std::vector<std::array<int, 5>>> vis;

		fillTrees(treemap, input);
		fillVisibility(vis, treemap.size(), treemap[0].size());
		calculateVisibilities(treemap, vis);
		printVisibilities(vis);
		std::cout << "Visible trees: " << countVisibilities(vis) << std::endl;
	}

	void part2() {
		std::ifstream input("Day08.txt");
		std::vector<std::vector<int>> treemap;
		std::vector<std::vector<std::array<int, 5>>> vis;

		fillTrees(treemap, input);
		fillVisibilityZero(vis, treemap.size());
		calculateViewLengths(treemap, vis);
		size_t max = calculateScenicScores(vis);
		printVisibilities(vis);
		std::cout << "Maximum scenic score: " << max << std::endl;
	}

	void main() {
		part2();
	}

}