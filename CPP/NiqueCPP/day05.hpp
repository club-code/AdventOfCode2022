#include "common.hpp"

#define NB_STACKS 9

using instruction = std::tuple<int,int,int>;

struct day05 {
    std::array<std::string, NB_STACKS> stacks;
    std::vector<instruction> instructions;

    template <typename F>
    std::string rearrange(F f);

    day05();

    std::string part_one();
    std::string part_two();
};