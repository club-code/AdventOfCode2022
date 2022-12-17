#include "day09.h"
#include <set>
#include <unordered_set>

using pairs = std::pair<int, int>;
struct queueState {};

inline int distance(pairs head, pairs queue) {
	return (std::max(std::abs(head.first - queue.first), std::abs(head.second - queue.second)));
}

inline bool isDiag(pairs head, pairs queue) {
	if (head.first == queue.first || head.second == queue.second) {
		return false;
	}
	return true;
}

void inline move(pairs& rope, char direction) {
	if (direction == 'D') {
		rope = { rope.first,rope.second - 1 };
	}
	else if (direction == 'U') {
		rope = { rope.first,rope.second + 1 };
	}
	else if (direction == 'L') {
		rope = { rope.first - 1,rope.second };
	}
	else {
		rope = { rope.first + 1,rope.second };
	}
}

int inline localisation(std::vector<std::string> input) {
	pairs queue = { 0,0 };
	pairs head = { 0,0 };
	std::set<pairs> localisationList = {};
	localisationList.insert(queue);
	for (auto& line : input) {
		auto movement = std::stoi(line.substr(2, line.size()));
		if (distance(head, queue) == 0) {
			move(head, line[0]);
			for (int i = 1; i < movement; i++) {
				move(head, line[0]);
				move(queue, line[0]);
				localisationList.insert(queue);
			}
		}
		else {
			for (int i = 1; i <= movement; i++) {
				move(head, line[0]);
				if (distance(head, queue) <= 1) continue;
				if (isDiag(head, queue)) {
					if (queue.first < head.first) {
						if (queue.second < head.second) { queue = { queue.first + 1,queue.second + 1 }; }
						else { queue = { queue.first + 1,queue.second - 1 }; }
					}
					else {
						if (queue.second < head.second) { queue = { queue.first - 1,queue.second + 1 }; }
						else { queue = { queue.first - 1,queue.second - 1 }; }
					}
					localisationList.insert(queue);
				}
				else {
					move(queue, line[0]);
					localisationList.insert(queue);
				}
			}
		}
	}
	return localisationList.size();
}

std::string inline transformToString(char dir,int value) {
	std::string mov;
	mov.append(1, dir);
	mov += " ";
	mov += std::to_string(value);
	return mov;
}

std::vector<std::string> inline pathOfQueue(std::vector<std::string> input) {
	pairs queue = { 0,0 };
	pairs head = { 0,0 };
	std::vector<std::string> inputQueue = {};
	for (auto& line : input) {
		auto movement = std::stoi(line.substr(2, line.size()));
		if (distance(head, queue) == 0) {
			move(head, line[0]);
			if (movement - 1 > 0) {
				inputQueue.push_back(transformToString(line[0],movement-1));
			}
			for (int i = 1; i < movement; i++) {
				move(head, line[0]);
				move(queue, line[0]);
			}
		}
		else {
			for (int i = 1; i <= movement; i++) {
				move(head, line[0]);
				if (distance(head, queue) <= 1) continue;
				if (isDiag(head, queue)) {
					if (queue.first < head.first) {
						inputQueue.push_back(transformToString('R', 1));
						if (queue.second < head.second) { 
							queue = { queue.first + 1,queue.second + 1 }; 
							inputQueue.push_back(transformToString('U', 1));
						}
						else { 
							queue = { queue.first + 1,queue.second - 1 }; 
							inputQueue.push_back(transformToString('D', 1));
						}
					}
					else {
						inputQueue.push_back(transformToString('L', 1));
						if (queue.second < head.second) { queue = { queue.first - 1,queue.second + 1 }; inputQueue.push_back(transformToString('U', 1));
						}
						else { queue = { queue.first - 1,queue.second - 1 }; inputQueue.push_back(transformToString('D', 1));}
					}
				}
				else {
					move(queue, line[0]);
					inputQueue.push_back(transformToString(line[0], 1));
				}
			}
		}
	}
	return inputQueue;
}

void day09::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('9');
	//input = { "R 4", "U 4", "L 3", "D 1", "R 4", "D 1", "L 5", "R 2" };
	input.resize(input.size() - 1);
	std::cout << localisation(input);
}

void day09::part2()
{
	//ne fonctionne pas : la diagonale ajoute une case visitée en plus, revoir cette partie de l'algo
	std::vector<std::string> input = AdventOfCode::GetDayInput('9');
	input = { "R 5", "U 8", "L 8", "D 3", "R 17", "D 10","L 25", "U 20" };
	//input = pathOfQueue(input);
	//input.resize(input.size() - 1);
	std::cout << localisation(input);
}
