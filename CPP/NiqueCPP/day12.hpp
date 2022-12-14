#include "common/common.hpp"

using matrix = std::vector<std::string>;
using pos = std::pair<int,int>;

struct day12 {
    matrix heightmap;

    uint8_t width;
    uint8_t height; 

    pos start;
    pos end;

    bool valid(const pos& p);
    std::list<pos> accessible(matrix& hm, const pos& p, const auto& visited);
    int bfs(matrix& hm, pos start, std::function<bool(const pos& p)> endCondition);

    day12();

    int part_one(); 
    int part_two();
};