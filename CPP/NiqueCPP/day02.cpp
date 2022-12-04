#include "day02.hpp"

day02::day02() {
    auto input = profile("Opening file day02", readFile, "inputs/day02.input");
    for (const auto& s : input) instructions.push_back(rps(s[0], s[2]));
}

int day02::part_one() {
    return std::accumulate(instructions.begin(), instructions.end(), 0,
        [](int sum, rps r) {
            sum += (r.second - 'X' + 1) + ((r.second - (r.first + 'X' - 'A') + 4)%3 * 3);
            return sum;
        });    
}

int day02::part_two() {
    return std::accumulate(instructions.begin(), instructions.end(), 0,
        [](int sum, rps r) {
            int played = (r.first - 'A') + (r.second - 'X' - 1);
            played = (played + 3)%3;
            sum += (r.second - 'X') * 3 + (played + 1);
            return sum;
        }); 
}

int main(int argc, char** argv) {
    day02 day02;
    std::cout << profile("Caching", [&day02](){day02.part_one(); return 0;}) << "\n";
    std::cout << profile("Part one", [&day02](){return day02.part_one();}) << "\n";
    std::cout << profile("Part two", [&day02](){return day02.part_two();}) << "\n";
}