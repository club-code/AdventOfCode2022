#include "common/common.hpp"

using matrix = std::vector<std::vector<int>>;

struct day08 {
    matrix trees;
    size_t size;

    bool isValid(int i, int j);
    int scenicScore(int i, int j);

    day08();

    int part_one();
    int part_two();
};
