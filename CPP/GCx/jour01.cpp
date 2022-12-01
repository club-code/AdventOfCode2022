#include "jour01.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

int jour01partie1(std::string path){
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()){
        throw std::invalid_argument("Could not open the following file : "+path);
    }
    std::string line;
    int max = 0;
    int cur = 0;
    while (std::getline(inputFile, line)){
        if (line.length() == 1){
            max = std::max(max, cur);
            std::cout << "cur = "<<cur<<" & max = "<<max<< std::endl;
            cur = 0;
        } else {
            cur += std::stoi(line);
        }
    }
    max = std::max(max, cur);
    return max;
}

int jour01partie2(std::string path){
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()){
            std::cerr << "Could not open the following file : "<<path <<std::endl;
            throw std::invalid_argument("Could not open the following file : "+path);
    }
    std::string line;
    std::vector<int> vec(3);
    int cur = 0;

    while (std::getline(inputFile, line)){
        if (line.length() == 1){
            // std::cout << "cur = "<<cur<<" & max = "<<max<< std::endl;
            if (cur > vec[0]){
                vec.insert(vec.begin(), cur);
            } else if (cur > vec[1]){
                vec.insert(vec.begin()+1, cur);
            } else if (cur > vec[2]){
                vec.insert(vec.begin()+2, cur);
            }
            if (vec.size() > 3){
                vec.pop_back();
            }
            cur = 0;
        } else {
            cur += std::stoi(line);
        }
    }
    if (cur > vec[0]){
        vec.insert(vec.begin(), cur);
    } else if (cur > vec[1]){
        vec.insert(vec.begin()+1, cur);
    } else if (cur > vec[2]){
        vec.insert(vec.begin()+2, cur);
    }
    if (vec.size() > 3){
        vec.pop_back();
    }

    return vec[0]+vec[1]+vec[2];
}


int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "1")==0){
        std::string path;
        if (std::strcmp(argv[2], "ex")==0){
            path = "./Input/01ex";
        } else if (std::strcmp(argv[2], "in")==0){
            path = "./Input/01in";
        }
        jour01partie1(path);
    } else if (argc == 3 && std::strcmp(argv[1], "2")==0){
        std::string path;
        if (std::strcmp(argv[2], "ex") == 0){
            path = "./Input/01ex";
        } else if (std::strcmp(argv[2], "in") == 0){
            path = "./Input/01in";
        }
        std::cout << "res = "<< jour01partie2(path);
    }
    return 0;
}