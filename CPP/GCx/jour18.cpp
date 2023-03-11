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

    Triplet(int arg_x, int arg_y, int arg_z){
        x = arg_x;
        y = arg_y;
        z = arg_z;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Triplet s){
    os << "Triplet {"<<s.x<<','<<s.y<<","<<s.z<<"}";
    return os;
}

inline bool operator<(const Triplet t1, const Triplet t2){
    return (t1.x < t2.x || (t1.x == t2.x && t1.y < t2.y) || (t1.x == t2.x && t1.y == t2.y && t1.z < t2.z)); 
}

bool are_adjacent(const Triplet t, const Triplet u){
    return std::abs(t.x-u.x) + std::abs(t.y-u.y) + std::abs(t.z-u.z) <=1;
}

int get_number_neighbours(std::set<Triplet> cubes, Triplet t){
    int voisins = 0;
    for (auto aux : {Triplet{1,0,0}, Triplet{-1, 0, 0}, Triplet{0, 1, 0}, Triplet{0, -1, 0}, Triplet{0, 0, 1}, Triplet{0, 0, -1}}){
        if (cubes.find(Triplet{t.x+aux.x, t.y+aux.y, t.z+aux.z})!=cubes.end()){
            voisins++;
            std::cout << Triplet{t.x+aux.x, t.y+aux.y, t.z+aux.z} << " est voisin de "<<t <<std::endl;
        }
    }
    std::cout << t << " : " << voisins << " voisins"<<std::endl;
    return voisins;
} 

int jour18partie1(std::vector<std::string> lines){
    std::set<Triplet> cubes;
    int intersections;
    for (auto line : lines){
        std::cout << Triplet{line} << std::endl; 
        cubes.insert(Triplet(line));
        intersections += get_number_neighbours(cubes, Triplet{line});
    }
    
    return 6*cubes.size() - 2*intersections;
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
        int res = jour18partie1(lines);
        std::cout << "Res = "<<res <<std::endl;
    }
    return 0;
}