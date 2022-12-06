#include "day05.hpp"

// Deleted line with stack numbers from input because we ball.
day05::day05() {
    auto input = profile("Opening file", readFile, "inputs/day05.input");
    bool isInstruction = false;
    for (const auto& s : input) {
        if (isInstruction) {
            auto split = split_string(s, " ");
            instructions.push_back(instruction(std::stoi(split[1]), std::stoi(split[3]), std::stoi(split[5])));
        } else {
            if (s.empty()) isInstruction = true;
            else {
                for (int i = 0; i < NB_STACKS; ++i) 
                    if (!std::isblank(static_cast<unsigned char>(s[1 + i*4]))) stacks[i].push_back(s[1 + i*4]);
            }
        }
    } 
}

template <typename F>
void move(int nb, std::string& src, std::string& dst, F f) {
    std::string tmp(nb, ' ');
    f(src.begin(), std::next(src.begin(), nb), tmp.begin());
    src.erase(0, nb);
    dst = tmp + dst;
}

template <typename F>
std::string day05::rearrange(F f) {
    auto stacksCopy = stacks;
    for (const auto& i : instructions) 
        move(std::get<0>(i), stacksCopy.at(std::get<1>(i) - 1), stacksCopy.at(std::get<2>(i) - 1), f);
    std::string ret;
    for (const auto& s : stacksCopy) ret.push_back(s.front());
    return ret;
}

std::string day05::part_one() {
    return rearrange(lift(std::reverse_copy));
}

std::string day05::part_two() {
    return rearrange(lift(std::copy));
}

int main(int argc, char** argv) {
    day05 day05;
    std::cout << profile("Part one", [&day05](){return day05.part_one();}) << "\n";
    std::cout << profile("Part two", [&day05](){return day05.part_two();}) << "\n";
}