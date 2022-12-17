#include <set>
#include <string>
#include <cstring>
#include "common.h"
#include <algorithm>
std::set<std::pair<int, int>> get_layout(std::vector<std::string> lines){
    std::set<std::pair<int, int>> rocks;
    for (auto it : lines){
        size_t curseur = 0;
        size_t begin = 0;
        std::vector<std::pair<int, int>> corners;
        while(curseur < it.length()){
            if (it[curseur]==' '){
                std::string corner = it.substr(begin, curseur-begin);
                corners.push_back({std::stoi(corner.substr(0, corner.find(','))), std::stoi(corner.substr(corner.find(',')+1, std::string::npos))});
                // std::cout << corners.back().first <<" & "<<corners.back().second<<std::endl;
                curseur+=4;
                begin = curseur;
            } else {
                curseur++;
            }
        }
        std::string corner = it.substr(begin, curseur-begin);
        corners.push_back({std::stoi(corner.substr(0, corner.find(','))), std::stoi(corner.substr(corner.find(',')+1, std::string::npos))});
        // std::cout << corners.back().first <<" & "<<corners.back().second<<std::endl;

        for (auto it_corner = corners.begin(); it_corner+1 != corners.end(); it_corner++){
            // std::cout << it_corner->first <<";"<<it_corner->second<<"=>"<<(it_corner+1)->first<<";"<<(it_corner+1)->second<<std::endl;
            auto begin_line = *it_corner;
            auto end_line = *(it_corner+1);
            int horizontal = 0;
            if (begin_line.first < end_line.first){
                horizontal = 1;
            } else if (begin_line.first > end_line.first){
                horizontal = -1;
            }

            int vertical = 0;
            if (begin_line.second < end_line.second){
                vertical = 1;
            } else if (begin_line.second > end_line.second){
                vertical = -1;
            }

            auto it_line = begin_line;
            while(it_line!=end_line){
                rocks.insert(it_line);
                // std::cout << it_line.first << ","<<it_line.second<< "->";
                it_line.first += horizontal;
                it_line.second += vertical;
            }
            rocks.insert(it_line);
        }
    }
    return rocks;
}

bool drop_sand_partie_1(std::set<std::pair<int,int>>& sand, std::set<std::pair<int, int>>& blocked, int ymax){
    int x = 500;
    int y = 0;
    while ((blocked.find({x, y+1}) == blocked.end() 
        || blocked.find({x-1, y+1}) == blocked.end() 
        || blocked.find({x+1, y+1}) == blocked.end()) 
        && (y<=ymax)){
        if (blocked.find({x,y+1})==blocked.end()){
            y++;
        } else {
            if (blocked.find({x-1, y+1})==blocked.end()){
                y++;
                x--;
            } else if (blocked.find({x+1, y+1})==blocked.end()){
                y++;
                x++;
            }
        }
    }
    if (blocked.find({x, y+1}) != blocked.end() && blocked.find({x-1, y+1}) != blocked.end() && blocked.find({x+1, y+1}) != blocked.end()){
        sand.insert({x, y});
        blocked.insert({x, y});
        return false;
    }
    if (y > ymax){
        return true;
    }
    return true;
}

bool drop_sand_partie_2(std::set<std::pair<int,int>>& sand, std::set<std::pair<int, int>>& blocked, int ymax){
    int x = 500;
    int y = 0;
    while ((blocked.find({x, y+1}) == blocked.end() 
        || blocked.find({x-1, y+1}) == blocked.end() 
        || blocked.find({x+1, y+1}) == blocked.end()) 
        && (y<=ymax)){
        if (blocked.find({x,y+1})==blocked.end()){
            y++;
        } else {
            if (blocked.find({x-1, y+1})==blocked.end()){
                y++;
                x--;
            } else if (blocked.find({x+1, y+1})==blocked.end()){
                y++;
                x++;
            }
        }
    }
    if ((blocked.find({x, y+1}) != blocked.end() && blocked.find({x-1, y+1}) != blocked.end() && blocked.find({x+1, y+1}) != blocked.end()) || y==ymax+1){
        sand.insert({x, y});
        blocked.insert({x, y});
        if (y==0 && x == 500){
            return true;
        } else {
            return false;
        }
    }

    return true;
}
void print_cave(std::set<std::pair<int, int>> sand, std::set<std::pair<int, int>> rocks, int xmin, int xmax, int ymin, int ymax){
    for (int y = 0; y <= ymax; y++){
        for (int x = xmin; x <= xmax; x++){
            if (y == 0 && x == 500){
                std::cout << '+';
            } else {
                if (sand.find({x, y})!=sand.end()){
                    std::cout << 'o';
                } else if (rocks.find({x, y})!=rocks.end()){
                    std::cout << '#';
                } else {
                    std::cout << '.';
                }
            }
        }
        std::cout << std::endl;
    }
}

int jour14partie1(std::set<std::pair<int, int>> rocks){
    int xmin = std::min_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first < b.first;
    }) ->first;

    int xmax = std::max_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first < b.first;
    }) ->first;

    int ymin = std::min_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.second < b.second;
    }) ->second;

    int ymax = std::max_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.second < b.second;
    }) ->second;

    std::set<std::pair<int,int>> sand;
    std::set<std::pair<int, int>> blocked{rocks};

    std::cout << "ymax = "<<ymax;
    while (!drop_sand_partie_1(sand, blocked, ymax)){
        print_cave(sand, rocks, xmin, xmax, ymin, ymax);
    }
    std::cout <<"Coucou"<<std::endl;
    std::cout << "Res = "<<sand.size(); 
    return sand.size();
}

int jour14partie2(std::set<std::pair<int, int>> rocks){
    int xmin = std::min_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first < b.first;
    }) ->first;

    int xmax = std::max_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first < b.first;
    }) ->first;

    int ymin = std::min_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.second < b.second;
    }) ->second;

    int ymax = std::max_element(rocks.begin(), rocks.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.second < b.second;
    }) ->second;

    std::set<std::pair<int,int>> sand;
    std::set<std::pair<int, int>> blocked{rocks};

    std::cout << "ymax = "<<ymax;
    while (!drop_sand_partie_2(sand, blocked, ymax)){
        // print_cave(sand, rocks, xmin, xmax, ymin, ymax);
    }
    std::cout <<"Coucou"<<std::endl;
    std::cout << "Res = "<<sand.size(); 
    return sand.size();
}

int main(int argc, char** argv){
    if (argc==3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (argc==3 && std::strcmp(argv[2], "ex")==0){
            path = "Input/14ex";
        } else if (argc==3 && std::strcmp(argv[2], "in")==0){
            path = "Input/14in";
        }

        std::vector<std::string> lines = readFile(path);
        auto rocks = get_layout(lines);
        int xmin = rocks.begin()->first;
        int xmax = rocks.begin()->first;
        int ymin = rocks.begin()->second;
        int ymax = rocks.begin()->second;
        for (auto it : rocks){
            xmax = std::max(xmax, it.first);
            xmin = std::min(xmin, it.first);
            ymax = std::max(ymax, it.second);
            ymin = std::min(ymin, it.second);
        }

        std::cout <<"["<<xmin <<","<<xmax<<"] - ["<<ymin<<","<<ymax<<"]"<<std::endl;
        
        for (int y = std::min(ymin, 0); y <= ymax; y++){
            for (int x = xmin; x <= xmax; x++){
                if (y==0 && x==500){
                    std::cout << '+';
                } else{
                    std::cout << (rocks.find({x, y})==rocks.end() ? '.' : '#');
                }
            }
            std::cout << std::endl;
        }
        if (argc == 3 && std::strcmp(argv[1], "1")==0){
            jour14partie1(rocks);
        } else if (argc==3 && std::strcmp(argv[1], "2")==0){
            jour14partie2(rocks);
        }
    }
}