#include "day07.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <numeric>
#include <vector>
#include "AdventOfAkasuna.h"
#include <stack>


struct Node {
	std::string name;
	Node* parent;
	std::vector<std::unique_ptr<Node>> children;
	int size;
};

inline std::unique_ptr<Node> constructTree(std::vector<std::string> input) {
	auto home=std::make_unique<Node>();
	home->name = "/";
	home->parent = nullptr;
	home->size = 0;
	Node* currentNode = home.get();
	//read 
	for (auto const& line : input) {
		if (line.find("/") != std::string::npos) {
			//pass
		}
		else if (line.find("$") != std::string::npos) {
			if (line.find("cd") != std::string::npos) {
				if (line.find("..") != std::string::npos) {
					currentNode = currentNode->parent;
				}
				else {
					std::string name = line.substr(5, line.size() - 5);
					for (auto const& child: currentNode->children) {
						if (child->name == name) {
							currentNode = child.get();
						}
					}
				}			
			}
		}
		else {
			auto node=std::make_unique<Node>();
			if (line.find("dir") != std::string::npos) {
				node->name = line.substr(4, line.size() - 4);
				node->size = 0;
			}
			else {
				for (int i = 0; i < line.size(); i++) {
					if (line[i] == ' ') {
						node->size = stoi(line.substr(0, i));
						node->name = line.substr(i + 1, line.size() - i - 1);
					}
				}
			}
			node->parent = currentNode;
			currentNode->children.push_back(move(node));
		}
	}
	return home;
}

inline int sumSize(Node* node) {
	if (node->size > 0) {
		return node->size;
	}
	else {
		int sum = 0;
		for (auto const& child : node->children) {
			sum += sumSize(child.get());
		}
		node->size = sum;
		return sum;
	}
}

inline int calculSumSuperior(Node* node) {
	//not a directory
	if (node->children.size() < 1) {
		return 0;
	}
	//a directory 
	else {
		int sum = 0;
		for (auto const& child : node->children) {
			if (child.get()->size <= 100000 && !child -> children.empty()) {
				sum += child.get()->size;
			}
			sum += calculSumSuperior(child.get());
		}
		return sum;
	}
}

inline void searchTheSmallest(Node* node, int sizeToFree, int& min) 
{
	if (node->size >= sizeToFree && node->size < min && !node->children.empty()) {
		min = node->size;
	}
	for (auto const& child : node->children) {
		searchTheSmallest(child.get(), sizeToFree, min);
	}
}


void day07::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('7');
	std::unique_ptr<Node> home = constructTree(input);
	sumSize(home.get());
	std::cout << calculSumSuperior(home.get());
}

void day07::part2() {
	std::vector<std::string> input = AdventOfCode::GetDayInput('7');
	std::unique_ptr<Node> home = constructTree(input);
	sumSize(home.get());
	int sizeToFree = 30000000 - (70000000 - home->size);
	int min = home->size;
	searchTheSmallest(home.get(), sizeToFree, min);
	std::cout << min;
}


