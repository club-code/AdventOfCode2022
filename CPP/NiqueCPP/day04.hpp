#include "common.hpp"

using range = std::pair<int,int>;

struct day04 {
    std::vector<std::pair<range,range>> pairs;

    day04();

    int part_one();
    int part_two();
};