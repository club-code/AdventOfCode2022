#include <string>
#include <cstring>
#include <algorithm>
#include "common.h"

struct Tree{
    //Default value is -1 because it may cause errors for trees on edge.
    int max_north{-1}, max_south{-1}, max_east{-1}, max_west{-1}; 
    int height;
    bool visible;
    Tree(int height): height{height}{}
};

std::vector<std::vector<Tree>> parseLines(std::vector<std::string> lines){
    std::vector<std::vector<Tree>> res;
    for(auto l : lines){
        std::vector<Tree> tree_line;
        for (auto c : l){
            std::cout << c-'0';
            tree_line.push_back(Tree{c-'0'});
        }
        std::cout << std::endl;
        res.push_back(tree_line);
    }
    return res;
}

void print(std::vector<std::vector<Tree>> trees){
    for (auto l: trees){
        for (auto c : l){
            std::cout << " "<<c.max_north<<"  ";
        }
        std::cout << std::endl;
        for (auto c : l){
            std::cout << c.max_west<<c.height<<c.max_east<<" ";
        }
        std::cout << std::endl;
        for (auto c : l){
            std::cout << " "<<c.max_south<<"  ";
        }
        std::cout << std::endl << std::endl;
    }   
}

int jour08partie1(std::vector<std::vector<Tree>> trees){
    for (size_t i = 1; i < trees.size(); i++){
        for (size_t j = 1; j < trees.size(); j++){
            std::cout << trees[i][j].height;
            trees[i][j].max_north = std::max(trees[i-1][j].max_north, trees[i-1][j].height);
            trees[i][j].max_west = std::max(trees[i][j-1].max_west, trees[i][j-1].height); 
        }
        std::cout << std::endl;
    }
    std::cout << "==="<<std::endl;
    // int count = 0;
    for (int i = trees.size()-2; i >= 0; i--){
        for(int j = trees.size()-2; j >= 0; j--){
            std::cout << trees[i][j].height<<"$";
            trees[i][j].max_south = std::max(trees[i+1][j].max_south, trees[i+1][j].height);
            trees[i][j].max_east = std::max(trees[i][j+1].max_east, trees[i][j+1].height);
        }
        std::cout << std::endl;
    }
    print(trees);

    int count = 0;
    for (auto l : trees){
        for (auto c: l){
            if (c.height > c.max_east || c.height > c.max_north || c.height >c.max_south || c.height > c.max_west){
                count++;
            }
        }
    }

    std::cout << "Res = "<<count<<std::endl;
    return count;
}

int get_view_distance(std::vector<std::vector<Tree>> trees, int l, int c){
    int res = 1;
    int max_size = trees.size()-1;
    std::cout << "Checking "<<l<<","<<c<<std::endl;
    std::cout << "Scenic score = ";
    for (std::pair<int, int> dir : std::vector<std::pair<int,int>>{{1, 0}, {-1,0}, {0, 1},{0, -1}}){
        int cursor = 1;
        while ((l+(dir.first*cursor)>=0) 
            && (l+(dir.first*cursor)<=max_size) 
            && (c+(dir.second*cursor)>=0)
            && (c+(dir.second*cursor)<=max_size)
            && (trees[l+dir.first*cursor][c+dir.second*cursor].height < trees[l][c].height)){
                cursor++;
            }
            if (! ((l+(dir.first*cursor)>=0) 
            && (l+(dir.first*cursor)<=max_size) 
            && (c+(dir.second*cursor)>=0) 
            && (c+(dir.second*cursor)<=max_size))){
                cursor--;
            }
        std::cout << cursor<<"*";
        res*=cursor;
    }
    std::cout << " = "<<res << std::endl;
    return res;
}

int jour08partie2(std::vector<std::vector<Tree>> trees){
    int max_view = -1;
    int max_i{-1}, max_j{-1};
    int max_size = trees.size()-1;
    for (int i = 1; i < max_size; i++){
        for (int j = 1; j < max_size; j++){
            int view_distance = get_view_distance(trees, i, j);
            if (view_distance > max_view){
                // std::cout << view_distance <<">"<<max_view<<std::endl;
                // std::cout << i <<","<<j<< ">"<< max_i <<","<<max_j<<std::endl;
                max_view = view_distance;
                max_i = i;
                max_j = j;
            }
        }
    }
    std::cout << "Max view = "<<max_view<<std::endl;
    return max_view;
}


int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (std::strcmp(argv[2], "in")==0){
            path = "Input/08in";
        } else if (std::strcmp(argv[2],"ex")==0){
            path = "Input/08ex";
        }
        auto lines = readFile(path);

        auto trees = parseLines(lines);
        if (std::strcmp(argv[1], "1")==0){
            jour08partie1(trees);
            return 1;
        } else if (std::strcmp(argv[1], "2")==0){
            jour08partie2(trees);
        }
    }
}