#include "day11.hpp"

day11::day11() {
    auto input = profile("Opening file", readFile, "inputs/day11.input");
    monkey curMonkey;
    for (const auto& s : input) {
        if (s.empty()) {
            monkeys.push_back(curMonkey);
            curMonkey.items.clear();
        } else {
            auto split = split_string(s, " ");
            if (split[0] == "Monkey") continue;
            if (split[2] == "Starting") {
                split = split_string(s, ", ");
                curMonkey.items.push_back(std::stoull(split[0].substr(18, 2)));
                for (size_t i = 1; i < split.size(); ++i) curMonkey.items.push_back(std::stoull(split[i]));
            } else if (split[2] == "Operation:") {
                curMonkey.opParameters = std::pair<std::string, std::string>(split[split.size()-2], split.back()); 
            } else if (split[2] == "Test:") {
                curMonkey.modulo = std::stoul(split.back());
            } else if (std::find(split.begin(), split.end(), "true:") != split.end()) {
                curMonkey.pass.first = std::stoi(split.back());
            } else if (std::find(split.begin(), split.end(), "false:") != split.end()) {
                curMonkey.pass.second = std::stoi(split.back());
            }
        }
    }
    monkeys.push_back(curMonkey);

    for (const auto& m : monkeys) lcm *= m.modulo;
}

void day11::turn(monkey& m, int divider, std::vector<monkey>& monkeys) {
    for (auto& item : m.items) {
        item = operation(item, m.opParameters) % lcm / divider;
        monkeys[destPass(item, m.modulo, m.pass)].items.push_back(item);
        m.nbPasses++;
    }
    m.items.clear();
}

unsigned long day11::run(int rounds, int divider) {
    auto copyMonkeys = monkeys;
    for (int i = 0; i < rounds; ++i) {
        for (auto& m : copyMonkeys) turn(m, divider, copyMonkeys);
    }
    unsigned long n1 = 0;
    unsigned long n2 = 0;
    for (const auto& m : copyMonkeys) {
        if (m.nbPasses > n1) {
            n2 = n1;
            n1 = m.nbPasses;
        } else if (m.nbPasses > n2) {
            n2 = m.nbPasses;
        }
    }
    return n1 * n2;
}

unsigned long day11::part_one() {
    return run(NB_ROUNDS_P1, DIVISER_P1);
}

unsigned long day11::part_two() {
    return run(NB_ROUNDS_P2, DIVISER_P2);
}

int main(int argc, char** argv) {
    day11 day11;
    std::cout << profile("Part one", [&day11](){return day11.part_one();}) << "\n";
    std::cout << profile("Part two", [&day11](){return day11.part_two();}) << "\n";
}   