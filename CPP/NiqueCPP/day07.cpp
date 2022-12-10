#include "day07.hpp"

std::optional<file*> parseLine(const std::string& s, file* cur) {
    auto split = split_string(s, " ");
    if (split[1] == "ls") return cur;
    else if (split[1] == "cd") {
        if (split[2] == "..") {
            return cur->parent;
        } else {
            for (auto& child : cur->children) {
                if (child->name == split[2]) {
                    return child.get();
                }
            }
        }
    } else if (std::isdigit(s[0])) {
        cur->children.push_back(std::make_unique<file>(std::stoi(split[0]), cur, split[1]));
    } else {
        cur->children.push_back(std::make_unique<file>(cur, split[1]));
    }
    return std::nullopt;
}

day07::day07() {
    auto input = profile("Opening file", readFile, "inputs/day07.input");
    root.children.push_back(std::make_unique<file>(&root, "/"));
    file* f = &root;
    for (const auto& s : input) {
        auto tmp = parseLine(s, f);
        if (tmp) f = tmp.value();
    }
}

unsigned long totalSize(const file& f) {
    if (f.val) return f.val.value();
    else return std::accumulate(f.children.begin(), f.children.end(), 0., 
        [](unsigned long sum, auto& f){sum+=totalSize(*f); return sum;});
}

unsigned long day07::part_one() {
    std::function<unsigned long(const file&)> sumSmallFolders = [&sumSmallFolders](const file& f) {
        if (!f.val) {
            unsigned long size = (totalSize(f) <= SMALL_SIZE) ? totalSize(f) : 0;
            size += std::accumulate(f.children.begin(), f.children.end(), 0.,
                [&sumSmallFolders](unsigned long sum, auto& f){sum+=sumSmallFolders(*f); return sum;});
            return size;
        } else return static_cast<unsigned long>(0);
    };
    return sumSmallFolders(root);
} 

unsigned long day07::part_two() {
    unsigned long spaceToDelete = totalSize(root) - FINAL_SPACE;
    unsigned long minDelete = TOTAL_DISK_SPACE;

    auto validMin = [&spaceToDelete](const unsigned long curMin, const unsigned long other) {
        if (other >= spaceToDelete) return std::min(curMin, other);
        else return curMin;
    };

    std::function<unsigned long(const file&, unsigned long&)> findMinDelete;
    findMinDelete = [&spaceToDelete, &findMinDelete, &validMin](const file& f, unsigned long& minDelete) {
        if (!f.val) {
            minDelete = validMin(minDelete, totalSize(f));
            for (auto&& child : f.children) 
                minDelete = validMin(minDelete, findMinDelete(*child, minDelete));
            return minDelete;
        } else return static_cast<unsigned long>(0);
    };
    return findMinDelete(root, minDelete);
}

int main(int argc, char** argv) {
    day07 day07;
    std::cout << profile("Part one", [&day07](){return day07.part_one();}) << "\n";
    std::cout << profile("Part two", [&day07](){return day07.part_two();}) << "\n";
}