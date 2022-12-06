#include "day04.h"
#include <iostream>
#include <string>
#include <algorithm> 
#include <numeric>
#include <vector>
#include "AdventOfAkasuna.h"

void day04::part1()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('4');
	int sum = 0;
	for (auto const& line : input) {
		if (line != "") {
			std::string first = line.substr(0, line.find(','));
			std::string second = line.substr(line.find(',') + 1);
			int one_firstzone = std::stoi(first.substr(0, first.find('-')));
			int two_firstzone = std::stoi(second.substr(0, second.find('-')));
			int one_secondzone = std::stoi(first.substr(first.find('-') + 1));
			int two_secondzone = std::stoi(second.substr(second.find('-') + 1));
			bool first_case = one_firstzone >= two_firstzone && one_secondzone <= two_secondzone;
			bool second_case = one_firstzone <= two_firstzone && one_secondzone >= two_secondzone;
			if (first_case || second_case)
			{
				sum++;
			}
		}
		
	}
	std::cout << sum;
}

void day04::part2()
{
	std::vector<std::string> input = AdventOfCode::GetDayInput('4');
	int sum = 0;
	for (auto const& line : input) {
		if (line != "") {
			std::string first = line.substr(0, line.find(','));
			std::string second = line.substr(line.find(',') + 1);
			int one_firstzone = std::stoi(first.substr(0, first.find('-')));
			int two_firstzone = std::stoi(second.substr(0, second.find('-')));
			int one_secondzone = std::stoi(first.substr(first.find('-') + 1));
			int two_secondzone = std::stoi(second.substr(second.find('-') + 1));
			bool first_case = one_secondzone < two_firstzone;
			bool second_case = one_firstzone > two_secondzone;
			if (!first_case && !second_case)
			{
				sum++;
			}
		}

	}
	std::cout << sum;
}
