#include "day08.hpp"

day08::day08() {
    auto input = profile("Opening file", readFile, "inputs/day08.input");
    for (const auto& s : input) {
        trees.push_back(stringToVector<int>(s, [](char c){return c - '0';}));
    }
    size = trees.size();
}

bool isBorder(int i, int j, size_t size) {
    return (i == 0 || j == 0 ||
            i == size-1 || j == size-1);
} 

bool day08::isValid(int i, int j) {
    if (isBorder(i,j,size)) return true;

    int treeVal = trees[i][j];
    int invalidDirections = 0;
    for (auto other_j = 0; other_j < j; ++other_j) 
        if (trees[i][other_j] >= treeVal) {invalidDirections++; break;}
    for (auto other_j = j+1; other_j < size; ++other_j) 
        if (trees[i][other_j] >= treeVal) {invalidDirections++; break;}
    for (auto other_i = 0; other_i < i; ++other_i) 
        if (trees[other_i][j] >= treeVal) {invalidDirections++; break;}
    for (auto other_i = i+1; other_i < size; ++other_i) 
        if (trees[other_i][j] >= treeVal) {invalidDirections++; break;}
    return (invalidDirections != 4);
}

int day08::scenicScore(int i, int j) {
    if (isBorder(i,j,size)) return 0;

    int treeVal = trees[i][j];
    int score = 1;
    for (auto other_j = j-1; other_j >= 0; --other_j) 
        if (trees[i][other_j] >= treeVal || other_j == 0) {score *= std::abs(j - other_j); break;}
    for (auto other_j = j+1; other_j < size; ++other_j) 
        if (trees[i][other_j] >= treeVal || other_j == size-1) {score *= std::abs(j - other_j); break;}
    for (auto other_i = i-1; other_i >= 0; --other_i) 
        if (trees[other_i][j] >= treeVal || other_i == 0) {score *= std::abs(i - other_i); break;}
    for (auto other_i = i+1; other_i < size; ++other_i) 
        if (trees[other_i][j] >= treeVal || other_i == size-1) {score *= std::abs(i - other_i); break;}
    return score;
}


int day08::part_one() {
    int totalSum = 0;
    for (int i = 0; i < size; ++i) 
        for (int j = 0; j < size; ++j) 
            totalSum += isValid(i,j);
    return totalSum;
}

int day08::part_two() {
    int curMax = 0;
    for (int i = 0; i < size; ++i) 
        for (int j = 0; j < size; ++j) 
            curMax = std::max(curMax, scenicScore(i,j));
    return curMax;
}

int main(int argc, char** argv) {
    day08 day08;
    std::cout << profile("Part one", [&day08](){return day08.part_one();}) << "\n";
    std::cout << profile("Part two", [&day08](){return day08.part_two();}) << "\n";
}