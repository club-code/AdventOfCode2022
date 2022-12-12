#include "common/common.hpp"

using point = std::pair<int,int>;

std::unordered_map<char, std::function<point(point&)>> moves {
    {'R', [](point& p){return point{p.first+1, p.second};}},
    {'U', [](point& p){return point{p.first, p.second+1};}},
    {'L', [](point& p){return point{p.first-1, p.second};}},
    {'D', [](point& p){return point{p.first, p.second-1};}},
};

struct day09 {
    std::deque<char> instructions;

    template <size_t n>
    int run();

    day09();

    int part_one();
    int part_two();
};