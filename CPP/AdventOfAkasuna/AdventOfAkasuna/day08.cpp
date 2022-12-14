#include "day08.h"

inline bool isVisible(int i, int j, std::vector<std::string> input) {
	int invalid = 0;
	for (int tree_i = 0; tree_i < i; tree_i++) {
		if (input[tree_i][j] >= input[i][j]) {
			invalid++;
			break;
		}
	}
	for (int tree_i = i+1; tree_i <input.size(); tree_i++) {
		if (input[tree_i][j] >= input[i][j]) {
			invalid++;
			break;
		}
	}
	for (int tree_j = 0; tree_j < j; tree_j++) {
		if (input[i][tree_j] >= input[i][j]) {
			invalid++;
			break;
		}
	}
	for (int tree_j = j+1; tree_j < input[0].size(); tree_j++) {
		if (input[i][tree_j] >= input[i][j]) {
			invalid++;
			break;
		}
	}
	if (invalid > 3) { return false; }
	return true;
}

inline int scenicScore(int i, int j, std::vector<std::string> input) {
	int score = 1;
	for (int tree_i = i-1; tree_i >=0; tree_i--) {
		if (input[tree_i][j] >= input[i][j] || tree_i==0) {
			score *= std::abs(i - tree_i);
			break;
		}
	}
	for (int tree_i = i+1; tree_i < input.size(); tree_i++) {
		if (input[tree_i][j] >= input[i][j] || tree_i== input.size() - 1) {
			score *= std::abs(i - tree_i);
			break;
		}
	}
	for (int tree_j = j - 1; tree_j >= 0; tree_j--) {
		if (input[i][tree_j] >= input[i][j] || tree_j == 0) {
			score *= std::abs(j - tree_j);
			break;
		}
	}
	for (int tree_j =j+1; tree_j < input[0].size(); tree_j++) {
		if (input[i][tree_j] >= input[i][j] || tree_j == input[0].size() - 1) {
			score *= std::abs(j - tree_j);
			break;
		}
	}
	return score;
}


void day08::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('8');
	//input = { "30373", "25512", "65332", "33549", "35390", ""};
	input.resize(input.size() - 1);
	int sum = input.size() * 2 + input[0].size() * 2 - 4;
	for (int i = 1; i < input.size() - 1; i++) {
		for (int j = 1; j < input[0].size() - 1; j++) {
			if (isVisible(i, j,input)) {
				sum++;
			}
		}
	}
	std::cout << sum;
}

void day08::part2()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('8');
	//input = { "30373", "25512", "65332", "33549", "35390", ""};
	input.resize(input.size() - 1);
	int score = 0;
	for (int i = 1; i < input.size() - 1; i++) {
		for (int j = 1; j < input[0].size() - 1; j++) {
			if (score < scenicScore(i,j,input) ){
				score = scenicScore(i,j,input);
			}
		}
	}
	std::cout << score;
}
