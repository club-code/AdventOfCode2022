#include "day06.hpp"

day06::day06() {
    signal  = profile("Opening file", readFile, "inputs/day06.input")[0];
}

bool uniqueChar(std::string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (s[i] == s[j]) return false;
        }
    }
    return true;
}

int day06::uniqueCharSubstringIndex(int window) {
    for (size_t i = 0; i < signal.size() - window; ++i) 
        if (uniqueChar(signal.substr(i, window))) return i+window;
    return -1;
}

// views::slide would've been cool but no C++23.
int day06::uniqueSlideIndex(int window) {
    size_t i = 0;
    while (i < signal.size() - window) {
        auto&& tmp = signal.substr(i, window);
        auto&& tmpset = std::unordered_set(tmp.begin(), tmp.end());
        if (tmpset.size() == (size_t)window) return i+window;
        i += window - tmpset.size();
    }
    return -1;
}

int day06::part_one() {
    return uniqueCharSubstringIndex(4);
}

int day06::part_two() {
    return uniqueCharSubstringIndex(14);
}

int main(int argc, char** argv) {
    day06 day06;
    std::cout << profile("Part one", [&day06](){return day06.part_one();}) << "\n";
    std::cout << profile("Part two", [&day06](){return day06.part_two();}) << "\n";
}
