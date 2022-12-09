#include "day09.hpp"

day09::day09() {
    auto input = profile("Opening file", readFile, "inputs/day09.input");
    for (const auto& s : input) 
        instructions.insert(instructions.end(), std::stoi(split_string(s, " ")[1]), s[0]);
}

inline int normalize(int i) {
    if (i>0) return 1;
    if (i<0) return -1;
    return 0;
}

point moveTail(point& head, point& tail) {
    point vec(head.first - tail.first, head.second - tail.second);
    if (std::abs(vec.first) < 2 && std::abs(vec.second) < 2) {
        return tail;
    } else {
        return point(tail.first + normalize(vec.first), 
                     tail.second + normalize(vec.second));
    }
}

point moveHead(point& head, char instruction) {
    return moves[instruction](head);
}

int day09::part_one() {
    point head(0,0);
    point tail(0,0);
    std::unordered_set<point, hashes::PairHash<int,int>> visited;
    for (const auto instruction : instructions) {
        head = moveHead(head, instruction);
        tail = moveTail(head, tail);
        visited.insert(tail);
    } 
    return visited.size();
}

int day09::part_two() {
    point head(0,0);
    std::array<point, 9> tails;
    std::fill(tails.begin(), tails.end(), point(0,0));
    std::unordered_set<point, hashes::PairHash<int,int>> visited;
    for (const auto instruction : instructions) {
        head = moveHead(head, instruction);
        tails.front() = moveTail(head, tails[0]);
        for (size_t i = 0; i < tails.size() - 1; ++i)
            tails[i+1] = moveTail(tails[i], tails[i+1]);
        visited.insert(tails.back());
    }
    return visited.size();
}

int main(int argc, char** argv) {
    day09 day09;
    std::cout << profile("Part one", [&day09](){return day09.part_one();}) << "\n";
    std::cout << profile("Part two", [&day09](){return day09.part_two();}) << "\n";
}