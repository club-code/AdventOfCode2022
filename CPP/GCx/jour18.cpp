#include "common.h"
#include <cstring>
#include <iostream>
#include <string>
#include <set>


std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}
struct Triplet{
    int x,y,z;

    Triplet(std::string arg){
        auto aux = split(arg, ",");
        x = std::stoi(aux[0]);
        y = std::stoi(aux[1]);
        z = std::stoi(aux[2]);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Triplet s){
    os << "Triplet {"<<s.x<<','<<s.y<<","<<s.z<<"}";
    return os;
}

bool are_adjacent(const Triplet t, const Triplet u){
    return std::abs(t.x-u.x) + std::abs(t.y-u.y) + std::abs(t.z-u.z) <=1;
}

int jour18partie1(std::vector<std::string> lines){
    std::set<Triplet> cubes;
    for (auto line : lines){
        std::cout << Triplet{line} << std::endl;
        cubes.insert(Triplet{line});
    }
    
    return 0;
}

int main(int argc, char** argv){
     if (argc == 3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (argc == 3 && std::strcmp(argv[2], "ex")==0){
            path = "Input/18ex";
        } else if (argc == 3 && std::strcmp(argv[2], "in")==0){
            path = "Input/18in";
        }

        std::vector<std::string> lines = readFile(path);
        for (std::string line : lines){
            std::cout << line << std::endl;
        }
        jour18partie1(lines);
    }
    return 0;
}