#include "day04.hpp"

day04::day04() {
    auto input = profile("Opening file", readFile, "inputs/day04.input");
    auto makeRange = [](std::string s) {
        return range(std::stoi(s.substr(0, s.find('-'))), std::stoi(s.substr(s.find('-')+1)));
    };
    for (const auto& s : input) {
        pairs.push_back(std::pair<range, range>(makeRange(split_string(s, ",")[0]), makeRange(split_string(s, ",")[1])));
    }
}

bool contains(const range& r, const range& other) {
    return ((r.first <= other.first && r.second >= other.second) || 
            (r.first >= other.first && r.second <= other.second));
}

bool overlaps(const range& r, const range& other) {
    return ((r.first >= other.first && r.first <= other.second) ||
            (r.second >= other.first && r.second <= other.second));
}

int day04::part_one() {
    return std::accumulate(pairs.begin(), pairs.end(), 0,
            [](int sum, std::pair<range, range> p) {
                sum += contains(p.first, p.second);
                return sum;
            });
}

int day04::part_two() {
    return std::accumulate(pairs.begin(), pairs.end(), 0,
            [](int sum, std::pair<range, range> p) {
                sum += (overlaps(p.second, p.first) || overlaps(p.first, p.second));
                return sum;
            });
}

int main(int argc, char** argv) {
    day04 day04;
    std::cout << profile("Part one", [&day04](){return day04.part_one();}) << "\n";
    std::cout << profile("Part two", [&day04](){return day04.part_two();}) << "\n";
}