#include "common.hpp"

struct day06 {
    std::string signal;
    int uniqueSlideIndex(int window);
    int uniqueCharSubstringIndex(int window);

    day06();

    int part_one();
    int part_two();
};