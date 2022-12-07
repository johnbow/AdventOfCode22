#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <stdexcept>

namespace Day07 {

	const std::regex cdMatcher("^\\$ cd ([a-z\\./]+)");
	const std::regex lsMatcher("^\\$ ls");
	const std::regex fileMatcher("([0-9]+) ([\\.a-z]+)");
	const std::regex dirMatcher("dir ([a-z]+)");

	enum class FileType { FILE, DIRECTORY };

	class File {

	private:
		const std::string name;
		const std::size_t size;
		const FileType type;

		File* parent;
		std::vector<File> entries;

	public:
		File(File* parent, const std::string name, const std::size_t size, FileType type) :
			parent{ parent }, name{ name }, size{ size }, type{ type } {}

		File(File* parent, const std::string name, const std::size_t size) :
			File(parent, name, size, FileType::FILE) {}

		File(File* parent, const std::string name) :
			File(parent, name, 0, FileType::DIRECTORY) {}

		const std::string& getName() const {
			return this->name;
		}

		const std::size_t getSize() const {
			return this->size;
		}

		const FileType getType() const {
			return this->type;
		}

		File* getParent() const {
			return this->parent;
		}

		void parseFileTree(std::ifstream& input) {
			std::smatch matches;
			std::string line;
			while (std::getline(input, line)) {
				if (std::regex_match(line, matches, cdMatcher)) {
					std::string to = matches[1];
					File* cdFile = this;
					if (to == "..") {										// move up one directory
						cdFile = this->getParent();
					}
					else if (to == "/") {									// move to root
						while (cdFile->parent != nullptr)
							cdFile = cdFile->parent;
					}
					else {													// move down one directory
						auto it = std::find_if(entries.begin(), entries.end(),
							[to](File& f) { return f.getName() == to; });
						if (it != entries.end())
							cdFile = &(*it);
						else
							throw std::runtime_error(std::string("Couldn't find entry: ") + to);
					}
					if (cdFile->getType() == FileType::DIRECTORY)
						cdFile->parseFileTree(input);
					else
						throw std::runtime_error(to + std::string(" is not a file."));
					return;
				}
				else if (std::regex_match(line, matches, lsMatcher)) {

				}
				else if (std::regex_match(line, matches, fileMatcher)) {
					const std::size_t size = std::stoi(matches[1]);
					File file(this, matches[2], size);
					this->entries.push_back(std::move(file));
				}
				else if (std::regex_match(line, matches, dirMatcher)) {
					File dir(this, matches[1]);
					this->entries.push_back(std::move(dir));
				}
				else {
					std::cout << "Couldn't identify line: " << line << std::endl;
				}
			}
		}

		void printFileTree(const std::string& prefix, char appendChar = '\t') const {
			for (const File& entry : this->entries) {
				if (entry.type == FileType::FILE) {
					std::cout << prefix << "- " << entry.getName() << " (file, size=" << entry.getSize() << ")" << std::endl;
				}
				else {
					std::cout << prefix << "- " << entry.getName() << " (dir)" << std::endl;
					entry.printFileTree(prefix + appendChar);
				}
			}
		}

		const size_t calculateSizeSumBelow(size_t limit, size_t& result) const {
			if (this->getType() == FileType::FILE)
				return this->getSize();
			size_t sum = 0;
			for (const File& entry : this->entries) {
				sum += entry.calculateSizeSumBelow(limit, result);
			}
			if (sum <= limit)
				result += sum;
			return sum;
		}

		const size_t getTotalSize() const {
			if (this->getType() == FileType::FILE)
				return this->getSize();
			size_t sum = 0;
			for (const File& entry : this->entries) {
				sum += entry.getTotalSize();
			}
			return sum;
		}

		const size_t findSpaceToDelete(size_t spaceToDelete, size_t& result) const {
			if (this->getType() == FileType::FILE)
				return this->getSize();
			size_t sum = 0;
			for (const File& entry : this->entries) {
				sum += entry.findSpaceToDelete(spaceToDelete, result);
			}
			if (sum >= spaceToDelete && sum < result)
				result = sum;
			return sum;
		}
	};


	void part1() {
		std::ifstream input("Day07.txt");
		std::string firstLine;
		std::getline(input, firstLine);	// ignore first line
		File root(nullptr, "/");
		root.parseFileTree(input);
		std::string pre("");
		root.printFileTree(pre);
		size_t sum = 0;
		root.calculateSizeSumBelow(100000, sum);
		std::cout << "Sum of size of directories below 100 000: " << sum << std::endl;
	}

	void part2() {
		std::ifstream input("Day07.txt");
		std::string firstLine;
		std::getline(input, firstLine);	// ignore first line
		File root(nullptr, "/");
		root.parseFileTree(input);
		size_t spaceToDelete = 30000000 - (70000000 - root.getTotalSize());
		size_t result = 70000000;
		root.findSpaceToDelete(spaceToDelete, result);
		std::cout << "Space to delete: " << result << std::endl;
	}

	void main() {
		part2();
	}

}