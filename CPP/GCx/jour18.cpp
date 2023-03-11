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
    int intersections = 0;
    for (auto line : lines){
        std::cout << Triplet{line} << std::endl; 
        cubes.insert(Triplet(line));
        intersections += get_number_neighbours(cubes, Triplet{line});
    }
    
    return 6*cubes.size() - 2*intersections;
}


size_t flood_fill(std::set<Triplet> cubes){
    size_t faces = 0; 
    std::vector<Triplet> stack{Triplet(1, 1, 1)};
    std::set<Triplet> seen;
    while(!stack.empty()){
        Triplet cur = stack.back();
        std::cout << "Seen = "<<cur << std::endl;
        stack.pop_back();
        if (seen.find(cur)==seen.end()){
            seen.insert(cur);
            for (auto t_aux : {Triplet{1,0,0}, Triplet{-1, 0, 0}, Triplet{0, 1, 0}, Triplet{0, -1, 0}, Triplet{0, 0, 1}, Triplet{0, 0, -1}}){
                Triplet cur_neighbour{cur.x + t_aux.x, cur.y + t_aux.y, cur.z + t_aux.z};
                if (cubes.find(cur_neighbour) != cubes.end()){
                    std::cout << cur_neighbour << " is a neighbour of "<<cur<<std::endl;
                    faces++;
                    std::cout << "faces : "<<faces<<std::endl;
                } else if (seen.find(cur_neighbour) == seen.end() 
                        && -1 <= cur_neighbour.x && cur_neighbour.x < 23
                        && -1 <= cur_neighbour.y && cur_neighbour.y < 23
                        && -1 <= cur_neighbour.z && cur_neighbour.z < 23){
                    std::cout << "Adding "<<cur_neighbour<<" to the stack"<<std::endl;
                    stack.push_back(cur_neighbour);
                }
            }
        }
    }
    return faces;
}

size_t jour18partie2(std::vector<std::string> lines){
    std::set<Triplet> cubes;
    for (auto line : lines){
        cubes.insert(Triplet(line));
    }

    return flood_fill(cubes);
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

        size_t res;
        if (argc ==3 && std::strcmp(argv[1], "1")==0){
            res = jour18partie1(lines);
        } else if (argc == 3 && std::strcmp(argv[1], "2")==0){
            res = jour18partie2(lines);
        }
        std::cout << "Res = "<<res <<std::endl;
    }
    return 0;
}