#include "common.hpp"

using rps = std::pair<char,char>;

struct day02 {
    std::vector<rps> instructions;

    day02();

    int part_one();
    int part_two();
};