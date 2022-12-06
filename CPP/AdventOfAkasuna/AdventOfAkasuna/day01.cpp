#include "day01.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <numeric>
#include <vector>
#include "AdventOfAkasuna.h"


void day01::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('1');
	int sum = 0;
	int max = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].empty()) {
			max = (sum >= max) ? sum : max;
			sum = 0;
		}
		else {
			sum += stoi(input[i]);
		}
	}
	std::cout << max;
}

void day01::part2()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('1');
	std::vector<int> max{ 0,0,0 };
	int sum = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i].empty()) {
			for (int j = 0; j < max.size(); j++) {
				if (sum >= max[j]) {
					max[j] = sum;
					break;
				}
			}
			sort(max.begin(), max.end());
			sum = 0;
		}
		else {
			sum += stoi(input[i]);
		}
	}
	std::cout << accumulate(max.begin(), max.end(), 0);
}
