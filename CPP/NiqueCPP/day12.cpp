#include "day12.hpp"

day12::day12() {
    heightmap = profile("Opening file", readFile, "inputs/day12.input");
    height = heightmap.size();
    width = heightmap[0].size();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (heightmap[i][j] == 'E') {
                end = std::pair<int,int>(i,j);
            } else if (heightmap[i][j] == 'S') {
                start = std::pair<int,int>(i,j);
            }
        }
    }
    heightmap[start.first][start.second] = 'a';
    heightmap[end.first][end.second] = 'z';
}

bool day12::valid(const pos& p) {
    return (p.first >= 0 && p.second >=0 &&
            p.first < height && p.second < width);
}

std::list<pos> day12::accessible(matrix& hm, const pos& p, const auto& visited) {
    std::list<pos> acc;
    auto access = [&](pos src, pos dest) {
        if (valid(dest) && visited.find(dest) == visited.end() && 
            hm[dest.first][dest.second] - hm[src.first][src.second] <= 1)
            acc.push_back(dest);
    }; 
    access(p, pos(p.first-1, p.second));
    access(p, pos(p.first, p.second-1));
    access(p, pos(p.first+1, p.second));
    access(p, pos(p.first, p.second+1));
    return acc;
}

int day12::bfs(matrix& hm, pos start, std::function<bool(const pos& p)> endCondition) {
    std::deque<std::pair<pos, int>> queue;
    std::unordered_set<pos, hashes::PairHash<int,int>> visited;
    auto visit = [&queue, &visited](const pos& p, int depth) {
        queue.emplace_back(p, depth);
        visited.insert(p);
    };
    visit(start, 0);
    while (!endCondition(queue.front().first)) {
        auto [p, depth] = queue.front();
        queue.pop_front();
        for (auto& neigh : accessible(hm, p, visited))
            visit(neigh, depth+1);
    }
    return queue.front().second;
}

matrix flip(matrix& heightmap) {
    matrix newMap = heightmap;
    for (auto& row : newMap)
        for (auto& c : row)
            c = 'z' + 'a' - c;
    return newMap;
}

int day12::part_one() {
    return bfs(heightmap, start, [&](const pos& p){return p == end;});
}

int day12::part_two() {
    matrix flipped = flip(heightmap);
    return bfs(flipped, end, [&](const pos& p){return flipped[p.first][p.second] == 'z';});
}

int main(int argc, char** argv) {
    day12 day12;
    std::cout << profile("Part one", [&day12](){return day12.part_one();}) << "\n";
    std::cout << profile("Part two", [&day12](){return day12.part_two();}) << "\n";
}