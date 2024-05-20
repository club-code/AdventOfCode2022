#include <cstring>
#include "common.h"
#include <vector>
#include <iostream>
#include <set>
#include <map>

using coords_t = std::pair<int, int>;
using color_map_t = std::map<coords_t, bool>;

inline std::ostream& operator<<(std::ostream& os, coords_t c){
    os << "{E: "<<c.first<<", NE: "<<c.second<<"}";
    return os;
} 
 
struct Hex
{
    coords_t coords = {0, 0};
    bool is_white = true;
};

coords_t get_coords_from_string(std::string str)
{
    auto itstr = str.begin();
    coords_t res = {0, 0};
    while (itstr != str.end())
    {
        if (*itstr == 'e'){
            res.first++;
            itstr++;
        } else if (*itstr == 'w'){
            res.first--;
            itstr++;
        } else if (*itstr == 'n' && *(itstr+1) == 'e'){
            res.second++;
            itstr+=2;
        } else if (*itstr == 's' && *(itstr+1) == 'w'){
            res.second--;
            itstr+=2;
        } else if (*itstr == 'n' && *(itstr+1) == 'w'){
            res.first--;
            res.second++;
            itstr+=2;
        } else { //if (*itstr == 's' && *(itstr+1) == 'e'){
            res.first++;
            res.second--;
            itstr+=2;
        } 
    }
    return res;
}

std::set<coords_t> get_black_tiles(std::vector<std::string> lines)
{
    std::set<coords_t> black_tiles{};
    for (auto str : lines){
        coords_t coords = get_coords_from_string(str);
        std::cout << coords << " : "<< str <<std::endl;
        if (black_tiles.find(coords) == black_tiles.end()){
            black_tiles.insert(coords);
        } else {
            black_tiles.erase(coords);
        }
    }
    return black_tiles;
} 

int part1(std::vector<std::string> lines)
{   
    
    return get_black_tiles(lines).size();
}

std::vector<coords_t> get_neighbours(coords_t tile){
    std::vector<coords_t> res;
    for (coords_t aux : std::vector<coords_t>{{1,0},{-1,0},{0,1},{0,-1},{-1,1},{1,-1}}){
        res.push_back({tile.first+aux.first, tile.second+aux.second});
    }
    return res;
}

color_map_t step0(std::set<coords_t> black_tiles){
    std::map<coords_t, bool> tile_is_black;
    for (coords_t tile : black_tiles){
        tile_is_black.insert({tile, true});
        auto neighbours = get_neighbours(tile);
        for (auto neigh : neighbours){
            if (tile_is_black.find(neigh) == tile_is_black.end() && black_tiles.find(neigh) == black_tiles.end()){
                bool is_neighbour_black = (black_tiles.find(neigh) != black_tiles.end());
                tile_is_black.insert({neigh, is_neighbour_black});
            }
        }
    }
    return tile_is_black;
}

std::set<coords_t> next_step(std::set<coords_t> black_tiles){
    std::map<coords_t, int> all_neighbours;
    for (const coords_t black_tile : black_tiles){
        for (const coords_t neighbour : get_neighbours(black_tile)){
            if (all_neighbours.find(neighbour) == all_neighbours.end()){
                all_neighbours.insert({neighbour, 1});
            } else {
                all_neighbours.at(neighbour)++;
            }
        }
    }

    std::set<coords_t> res;
    for(auto it = all_neighbours.begin(); it != all_neighbours.end(); it++){
        // std::cout << it->first <<" "<< (black_tiles.find(it->first) != black_tiles.end() ? "black " : "white ");
        // std::cout << it->second << "->";
        if (black_tiles.find(it->first) != black_tiles.end() && (it->second == 1 || it -> second == 2)){
            res.insert(it->first);
            // std::cout << " black" <<std::endl;
        } else if (black_tiles.find(it->first) == black_tiles.end() && it->second == 2){
            res.insert(it->first);
            // std::cout << " black" <<std::endl;
        } else {
            // std::cout << " white" <<std::endl;
        }
    }
    return res;
}

int part2(std::vector<std::string> lines)
{
    auto black_tiles = get_black_tiles(lines);

    // std::cout << "====="<<std::endl;
    // for (auto const tile_and_color : tile_is_black){
    //     std::cout << tile_and_color.first << " : "<< (tile_and_color.second ? "black" : "white") <<std::endl;
    // }

    std::cout << "Day 0 : " << black_tiles.size() << " black tiles"<<std::endl;
    for (int i = 1; i <= 100; i++){
        black_tiles = next_step(black_tiles);
        std::cout << "Day "<<i<<" : " << black_tiles.size() << " black tiles"<<std::endl;
    }
    return black_tiles.size();
}

int main(int argc, char **argv)
{
    if (argc == 3 && std::strcmp(argv[1], "1") == 0)
    {
        std::string path;
        if (std::strcmp(argv[2], "ex") == 0)
        {
            path = "./Input/2020-24ex";
        }
        else if (std::strcmp(argv[2], "in") == 0)
        {
            path = "./Input/2020-24in";
        }
        auto lines = readFile(path);
        auto res = part1(lines);
        std::cout <<"Res = "<<res<<std::endl;
    }
    else if (argc == 3 && std::strcmp(argv[1], "2") == 0)
    {
        std::string path;
        if (std::strcmp(argv[2], "ex") == 0)
        {
            path = "./Input/2020-24ex";
        }
        else if (std::strcmp(argv[2], "in") == 0)
        {
            path = "./Input/2020-24in";
        }
        auto lines = readFile(path);
        auto res = part2(lines);
        std::cout <<"Res = "<<res<<std::endl;
    }
    // return 0;
    if (argc == 3 && std::strcmp(argv[1], "1") == 0){
        std::string path;
    }
    // std::cout << get_coords_from_string("NENESESWESWWWNE") << std::endl;
    // std::cout << get_coords_from_string("NESESW") << std::endl;
}