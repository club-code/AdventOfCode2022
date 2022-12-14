#include "day06.h"


inline bool checkSequence(std::string sequence) {
	for (int i = 0; i < sequence.size() - 1; i++) {
		for (int j = i + 1; j < sequence.size(); j++) {
			if (sequence[i] == sequence[j]) {
				return false;
			}
		}
	}
	return true;
}


void day06::part1(int successiv)
{
	std::string input = AdventOfCode::GetDayInput('6')[0];
	int cursor = 0;
	bool found = false;
	while (!found) {
		found = checkSequence(input.substr(cursor, successiv));
		if (!found) { cursor++; }
	}
	std::cout << cursor + successiv;
}

void day06::part2()
{
	day06::part1(14);

}
