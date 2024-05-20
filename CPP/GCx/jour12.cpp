#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <limits>
#include <memory>
#include <algorithm>
#include "common.h"
struct Node {
    std::set<std::shared_ptr<Node>> neighbours;
    int height;
    char chara;
    std::shared_ptr<Node> parent;
    bool seen = false;
    int min_distance{std::numeric_limits<int>::max()};
    Node(char arg){
        switch (arg)
        {
        case 'S':
            height = 0;
            break;
        case 'E':
            height = 'z'-'a';
            break;
        default:
            height = arg-'a';
            break;
        }
        chara = arg;
    }
};

void link(std::shared_ptr<Node> a, std::shared_ptr<Node> b){
    if (b->height-a->height<=1){
        a->neighbours.insert(b);
    }
    if (a->height-b->height<=1){
        b->neighbours.insert(a);
    }
}

bool comp(std::shared_ptr<Node> a, std::shared_ptr<Node> b){
    return (a->min_distance < b->min_distance);
}

int Dijkstra(std::shared_ptr<Node> start){
    auto current_node = start;
    current_node->min_distance = 0;
    std::set<std::shared_ptr<Node>> not_seen;
    for (auto it : current_node->neighbours){
        not_seen.insert(it);
        it->min_distance = current_node->min_distance+1;
        it->parent = start;
    }
    while (current_node->chara != 'E' && !not_seen.empty()){
        auto min_node = std::min_element(not_seen.begin(), not_seen.end(), [](std::shared_ptr<Node> a, std::shared_ptr<Node>b)->bool {
            return a->min_distance < b->min_distance;
        });

        current_node = *min_node;
        if (current_node->chara == 'E'){
            std::cout << "Ding ding ding !!"<<std::endl;
        }
        // std::cout << "current node = "<<current_node->chara<<std::endl;
        // std::cout << "neighbours size = "<<current_node->neighbours.size()<<std::endl;
        current_node->seen = true;
        not_seen.erase(current_node);

        for (auto it : current_node->neighbours){
            if (it->chara == 'E'){
                std::cout << "Found neighbour E !!" <<std::endl;
            }
            if (it->min_distance > current_node->min_distance+1){
                it->min_distance = current_node->min_distance+1;
                it->parent = current_node;
            }

            if (!it->seen){
                not_seen.insert(it);
            }
        }
    }
    
    if (current_node->chara != 'E'){
        return std::numeric_limits<int>::max();
    }
    
    int i =0;
    while (current_node != start){
        i++;
        std::cout << current_node->chara <<"<-";
        current_node = current_node->parent;
    }
    std::cout << current_node->chara<<std::endl;
    return i;
}

int flood_fill(std::shared_ptr<Node> start){
    std::set<std::shared_ptr<Node>> front;
    front.insert(start);
    start->seen = true;

    int i = 1;
    while (!front.empty()){
        std::set<std::shared_ptr<Node>> next_front;
        for(auto it : front){
            for (auto it2 : it->neighbours){
                if (it2->chara == 'E'){
                    std::cout << "Found E at step "<<i<<std::endl;
                    return i;
                } else {
                    if (!it2->seen){
                        next_front.insert(it2);
                        it2->seen = true;
                    }
                }
            }
        }
        i++;
        front = next_front;
    }
    return -1;
}

void reset_grid(std::vector<std::vector<std::shared_ptr<Node>>> vec){
    for (auto it1 : vec){
        for (auto it2 : it1){
            it2->seen = false;
            it2->min_distance = std::numeric_limits<int>::max();
        }
    }
}

int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (argc == 3 && std::strcmp(argv[2], "in")==0){
            path = "Input/12in";
        } else if (argc == 3 && std::strcmp(argv[2],"ex")==0){
            path = "Input/12ex";
        }
        
        std::vector<std::string> lines = readFile(path);
        int m = lines.size();   
        int n = lines[0].size();
        std::vector<std::vector<std::shared_ptr<Node>>> grid;

        std::shared_ptr<Node> start;
        std::vector<std::shared_ptr<Node>> starts_position;
        for (int i = 0; i < m; i++){
            grid.push_back(std::vector<std::shared_ptr<Node>>());
            for (int j = 0; j < n; j++){
                grid[i].push_back(std::make_shared<Node>(lines[i][j]));
                if (lines[i][j]=='S'){
                    start = grid[i][j];
                }

                if (lines[i][j]=='S' || lines[i][j]=='a'){
                    starts_position.push_back(grid[i][j]);
                }
            }
        }
        
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (i != m-1){
                    link(grid[i][j], grid[i+1][j]);
                }
                if (j != n-1){
                    link(grid[i][j], grid[i][j+1]);
                }
            }
        }
        // flood_fill(start);
        int res1 = Dijkstra(start);
        std::cout << "Res partie 1 = "<<res1<<std::endl;

        int cur_min = std::numeric_limits<int>::max();
        for (auto it : starts_position){
            reset_grid(grid);
            int res2 = Dijkstra(it);
            cur_min = std::min(cur_min, res2);
        }
        std::cout << "Res 2 aux = " << cur_min <<std::endl;
    }
}