#include "day01.hpp"

day01::day01() {
    auto input = profile("Opening file day01.input", readFile, "inputs/day01.input");
    int cal = 0;
    for (const auto& s : input) {
        if (s.empty()) {
            calories.push_back(cal);
            cal = 0;
        } else {
            cal += std::stoi(s);
        }
    }
    calories.push_back(cal);
}

int day01::part_one() {
    return *std::max_element(calories.begin(), calories.end());
}

int day01::part_two() {
    int tot_cal = 0;
    for (int i = 0; i < 3; ++i) {
        tot_cal += *std::max_element(calories.begin(), calories.end());
        calories.erase(std::max_element(calories.begin(), calories.end()));
    }
    return tot_cal;
}

int main(int argc, char** argv) {
    day01 day01;
    std::cout << profile("Part one", [&day01](){return day01.part_one();}) << "\n";
    std::cout << profile("Part two", [&day01](){return day01.part_two();}) << "\n";
}