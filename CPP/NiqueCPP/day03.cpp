#include "day03.hpp"

day03::day03() {
    input = profile("Opening file", readFile, "inputs/day03.input");
}

inline int priority(char c) {
    if (c <= 'Z') return c - 'A' + 27;
    else return c - 'a' + 1;
}

char commonChar(std::string s) {
    for (const auto & c : s.substr(0, s.size()/2))
        if (s.substr(s.size()/2).find(c) != std::string::npos) return c;
    return '0';
}

char threeCommon(std::string s1, std::string s2, std::string s3) {
    for (const auto& c : s1)
        if (s2.find(c) != std::string::npos && s3.find(c) != std::string::npos) return c;
    return '0';
}

int day03::part_one() {
    int priorityTotal = 0;
    for (const auto& s : input)
        priorityTotal += priority(commonChar(s));
    return priorityTotal;
}

int day03::part_two() {
    int priorityTotal = 0;
    for (size_t i = 0; i < input.size(); i+=3) 
        priorityTotal += priority(threeCommon(input[i], input[i+1], input[i+2]));
    return priorityTotal;
}

int main(int argc, char** argv) {
    day03 day03;
    std::cout << profile("Part one", [&day03](){return day03.part_one();}) << "\n";
    std::cout << profile("Part two", [&day03](){return day03.part_two();}) << "\n";
}
