#include <cstring>
#include <string>
#include <vector>
#include "common.h"
#include <memory>
#include <queue>
struct Cost{
    int ore = 0;
    int clay = 0;
    int obsidian = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Cost c){
    os << "Cost{";
    if (c.ore != 0){
        os << "ore = "<<c.ore<<';';
    }
    if (c.clay != 0){
        os << "clay = "<<c.clay<<';';
    }
    if (c.obsidian != 0){
        os << "obsidian = "<<c.obsidian<<';';
    }
    os <<"}";
    return os;
}

inline bool operator==(const Cost c1, const Cost c2){
    return (c1.ore == c2.ore) && (c1.clay == c2.clay)&& (c1.obsidian == c2.obsidian);
}

struct Blueprint{
    int id;
    struct Cost ore_robot_cost;
    struct Cost clay_robot_cost;
    struct Cost obsidian_robot_cost;
    struct Cost geode_robot_cost;

    Blueprint(std::string s);
};

inline std::ostream& operator<<(std::ostream& os, const Blueprint b){
    os <<"Blueprint "<< b.id << ":"<<std::endl;
    os << "    ore robot cost : "<<b.ore_robot_cost<<std::endl;
    os << "    clay robot cost : "<<b.clay_robot_cost<<std::endl;
    os << "    obsidian robot cost : "<<b.obsidian_robot_cost<<std::endl;
    os << "    geode robot cost : "<<b.geode_robot_cost<<std::endl;

    return os;
}

inline bool operator==(const Blueprint a, const Blueprint b){
    return a.id == b.id && a.ore_robot_cost == b.ore_robot_cost && a.clay_robot_cost == b.clay_robot_cost 
        && a.obsidian_robot_cost == b.obsidian_robot_cost && a.geode_robot_cost == b.geode_robot_cost;
}

Blueprint::Blueprint(std::string s){
    size_t i1 = 10;
    size_t i2 = ('0'<=s[i1+1] && s[i1+1]<='9') ? i1+1 : i1;
    // std::cout <<"i1:i2 ="<< s.substr(i1, i2-i1+1)<<std::endl;
    id = std::stoi(s.substr(i1, i2-i1+1));

    size_t i3 = i2+24;
    size_t i4 = ('0'<=s[i3+1] && s[i3+1]<='9') ? i3+1 : i3;
    // std::cout << "i3:i4 ="<<s.substr(i3, i4-i3+1)<<std::endl;
    ore_robot_cost = Cost{ore : std::stoi(s.substr(i3, i4-i3+1))};

    size_t i5 = i4+29;
    size_t i6 = ('0'<=s[i5+1] && s[i5+1]<='9') ? i5+1 : i5;
    // std::cout << "i5:i6 ="<<s.substr(i5, i6-i5+1)<<std::endl;
    clay_robot_cost = Cost{ore : std::stoi(s.substr(i5, i6-i5+1))};

    size_t i7 = i6+33;
    size_t i8 = ('0'<=s[i7+1] && s[i7+1]<='9') ? i7+1 : i7;
    // std::cout << "i7:i8 ="<<s.substr(i7, i8-i7+1)<<std::endl;
    
    size_t i9 = i8+10;
    size_t i10 = ('0'<=s[i9+1] && s[i9+1]<='9') ? i9+1 : i9;
    // std::cout << "i9:i10 ="<<s.substr(i9, i10-i9+1)<<std::endl;
    obsidian_robot_cost = Cost{ore : std::stoi(s.substr(i7, i8-i7+1)), clay : std::stoi(s.substr(i9, i10-i9+1))};

    size_t i11 = i10+31;
    size_t i12 = ('0'<=s[i11+1] && s[i11+1]<='9') ? i11+1 : i11;
    // std::cout << "i11:i12 ="<<s.substr(i11, i12-i11+1)<<std::endl;

    size_t i13 = i12+10;
    size_t i14 = ('0'<=s[i13+1] && s[i13+1]<='9') ? i13+1 : i13;
    // std::cout << "i13:i14 ="<<s.substr(i13, i14-i13+1)<<std::endl;
    geode_robot_cost = Cost{ore : std::stoi(s.substr(i11, i12-i11+1)), obsidian : std::stoi(s.substr(i13, i14-i13+1))};
}

struct State{
    std::shared_ptr<Blueprint> blueprint;
    int minutes = 0;
    int ore_robots = 1, clay_robots = 0, obsidian_robots = 0, geode_robots = 0;
    int ore = 0, clay = 0, obsidian = 0, geode = 0;

    void harvest(){
        ore += ore_robots;
        clay += clay_robots;
        obsidian += obsidian_robots;
        geode += geode_robots;
    };

    void produce(){

    }
};

void get_next_states(std::queue<State> states, State current_state){
    
}

std::queue<State> unwind(std::queue<State> states){
    while (!states.empty()){
        State cur_state = states.front();
        states.pop();
        cur_state.harvest();

        cur_state.
    }
}

size_t jour19partie1(std::vector<std::string> lines){
    std::vector<std::shared_ptr<Blueprint>> blueprints;
    std::queue<State> states;
    int i = 0;
    for (auto line : lines){
        blueprints.push_back(std::make_shared<Blueprint>(Blueprint{line}));
        State s{.blueprint = *(blueprints.end()-1)};
        states.push(s);
        // std::cout << ((blueprints.end()-1)->get()) << " && " << &(*((states.end()-1)->blueprint))<<std::endl;
        blueprints.back()->id = -i++;
        std::cout << states.back().blueprint->id << std::endl;
    }

    
    return 0;
}

int main(int argc, char** argv){
     if (argc == 3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (argc == 3 && std::strcmp(argv[2], "ex")==0){
            path = "Input/19ex";
        } else if (argc == 3 && std::strcmp(argv[2], "in")==0){
            path = "Input/19in";
        }

        std::vector<std::string> lines = readFile(path);
        for (std::string line : lines){
            std::cout << line << std::endl;
        }

        size_t res;
        if (argc ==3 && std::strcmp(argv[1], "1")==0){
            res = jour19partie1(lines);
        }
        // else if (argc == 3 && std::strcmp(argv[1], "2")==0){
        //     res = jour19partie2(lines);
        // }
        std::cout << "Res = "<<res <<std::endl;
    }
    return 0;
}