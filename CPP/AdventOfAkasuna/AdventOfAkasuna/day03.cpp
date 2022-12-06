#include "day03.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <numeric>
#include <vector>
#include "AdventOfAkasuna.h"

inline int convertToPriority(char c) {
	if (c == toupper(c)) { return c - 'A' + 27; }
	else { return c - 'a' + 1; }
}

void day03::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('3');
	int sum = 0;
	for (int i = 0; i < input.size(); i++) {
		for (auto c : input[i].substr(0, input[i].size()/2)) {
			if (input[i].substr(input[i].size()/2, input[i].size()+1).find(c) != std::string::npos) {
				sum += convertToPriority(c);
				break;
			}
		}	
	}
	std::cout << sum;
}

void day03::part2()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('3');
	int sum = 0;
	for (int i = 0; i < input.size(); i+=3) {
		for (auto c : input[i]) {
			if (input[i+1].find(c) != std::string::npos && input[i + 2].find(c) != std::string::npos) {
				sum += convertToPriority(c);
				break;
			}
		}
	}
	std::cout << sum;

}
