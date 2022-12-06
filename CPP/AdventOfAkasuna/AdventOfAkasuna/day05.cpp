#include "day05.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <numeric>
#include <vector>
#include "AdventOfAkasuna.h"
#include <stack>


inline std::pair<std::vector<std::stack<char>>,int> ParseInput(std::vector<std::string> input) {
	
	int nbStack = 1; //nb column
	int biggestStack = 0; //nb line
	for (int i = 0; i < input.size(); i++) {	
		if (input[i].length() < 1) {
			biggestStack = i - 1;
			while (nbStack < input[biggestStack].size()) {
				nbStack += 4;
			}
			nbStack = (nbStack - 1) / 4;
			break;
		}
	}
	std::vector<std::stack<char>> stacks(nbStack);
	for (int i = biggestStack-1; i >= 0; i--) {
		int lenghtOfLine = 0;
		while (lenghtOfLine*4+1 < input[i].size()) {
			if (input[i][lenghtOfLine * 4 + 1] != ' ') {
				stacks[lenghtOfLine].push(input[i][lenghtOfLine * 4 + 1]);
			}
			lenghtOfLine++;
		}
	}

	return std::make_pair(stacks,biggestStack+2);
}

void day05::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('5');
	std::vector<std::stack<char>> stacks = ParseInput(input).first;
	int start = ParseInput(input).second;
	for (int i = start; i < input.size()-1; i++) {
		//"move 1 from 3 to 9"
		int nb = std::stoi(input[i].substr(input[i].find("move")+5, input[i].find("from")-6));
		int startStack = std::stoi(input[i].substr(input[i].find("from") + 5, input[i].find("to") - 4));
		int endStack = std::stoi(input[i].substr(input[i].find("to") + 3));
		for (int j = 0; j < nb; j++) {
			char data = stacks[startStack - 1].top();
			stacks[startStack - 1].pop();
			stacks[endStack - 1].push(data);
		}
	}

	auto s = new std::string();
	for (int i = 0; i < stacks.size(); i++) {
		s->push_back(stacks[i].top());
	}
	std::cout << *s;
}

void day05::part2()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('5');
	std::vector<std::stack<char>> stacks = ParseInput(input).first;
	int start = ParseInput(input).second;
	for (int i = start; i < input.size() - 1; i++) {
		//"move 1 from 3 to 9"
		const int nb = std::stoi(input[i].substr(input[i].find("move") + 5, input[i].find("from") - 6));
		int startStack = std::stoi(input[i].substr(input[i].find("from") + 5, input[i].find("to") - 4));
		int endStack = std::stoi(input[i].substr(input[i].find("to") + 3));
		auto data = std::vector<char>();
		for (int j = 0; j < nb; j++) {
			data.push_back(stacks[startStack - 1].top());
			stacks[startStack - 1].pop();
		}
		for (int l = nb-1; l > -1; l--) {
			stacks[endStack - 1].push(data[l]);
		}
		
	}

	auto s = new std::string();
	for (int i = 0; i < stacks.size(); i++) {
		s->push_back(stacks[i].top());
	}
	std::cout << *s;
}
