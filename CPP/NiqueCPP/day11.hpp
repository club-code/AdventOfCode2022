#include "common/common.hpp"

#define NB_ROUNDS_P1 20
#define NB_ROUNDS_P2 10000
#define DIVISER_P1 3
#define DIVISER_P2 1

std::function<unsigned long(unsigned long, const std::pair<std::string, std::string>)> operation = [](unsigned long old, const std::pair<std::string, std::string>& opParameters) {
                    return (opParameters.first == "+") ? 
                    old + std::stoi(opParameters.second) : 
                    old * ((opParameters.second=="old") ? old : std::stoi(opParameters.second));};

auto destPass = [](long x, const int modulo, const std::pair<int,int>& pass) {
    return (x % modulo == 0) ? pass.first : pass.second;
};

struct monkey {
    std::vector<long> items;
    std::pair<std::string, std::string> opParameters;
    int modulo;
    std::pair<int, int> pass;
    int nbPasses = 0;
};

struct day11 {
    std::vector<monkey> monkeys;
    int lcm = 1;

    void turn(monkey& m, int divider, std::vector<monkey>& monkeys);
    unsigned long run(int rounds, int divider);

    day11();

    unsigned long part_one();
    unsigned long part_two();
};