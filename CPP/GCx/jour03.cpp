
#include "jour03.h"

#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>

int priority(char ch){
    return ch+(ch<=90 ? -38 : -96);
}

std::vector<std::string> readFile(std::string path){
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()){
        std::cerr << "Could not open the file "<<path<<std::endl;
        throw std::invalid_argument("Could not open the file "+path);
    }
    std::string line;
    std::vector<std::string> res;
    while (std::getline(inputFile, line)){
        res.push_back(line);
    }
    return res;
}

char findCommonCharPartie1(std::string s1, std::string s2){
    for (auto c1 : s1){
        for (auto c2 : s2){
            if (c1 == c2){
                return c1;
            }
        }
    }
    return '0'; //On n'y arrive jamais
}

char findCommonCharPartie2(std::string s1, std::string s2, std::string s3){
    std::vector<char> s1Ands2;
    for (auto c1 : s1){
        for (auto c2 : s2){
            if (c1 == c2){
                s1Ands2.push_back(c1);
            }
        }
    }
    for (auto caux : s1Ands2){
        for (auto c3 : s3){
            if (caux == c3){
                return caux;
            }
        }
    }
    return '0'; // On n'y arrive jamais
}

int parseJour03partie1(std::vector<std::string> lines){
    std::vector<char> aux_char;
    int res = 0;
    for (std::string line : lines){
        aux_char.push_back(findCommonCharPartie1(line.substr(0, line.length()/2), line.substr(line.length()/2, line.length()/2)));
        res+=priority(findCommonCharPartie1(line.substr(0, line.length()/2), line.substr(line.length()/2, line.length()/2)));
    }
    return res;
}

int parseJour03partie2(std::vector<std::string> lines){
    std::vector<char> aux_char;
    int res = 0;
    // for (auto it = 0; it < lines.size(); it+=3){
    //     std::cout <<"Begin :" << lines[it] << "-"<<lines[it+1]<<"-"<<lines[it+2]<<std::endl;
    //     std::cout << findCommonCharPartie2(lines[it], lines[it+1], lines[it+2]) << std::endl;
    //     res+= priority(findCommonCharPartie2(lines[it], lines[it+1], lines[it+2]));
    // }
    for (auto it = lines.begin(); it < lines.end(); it+=3){
        std::cout << *it <<std::endl;
        std::cout << *(it+1) << std::endl;
        std::cout << *(it+2) << std::endl;
        std::cout << "Begin :" << *it << " " << *(it+1) << " " << *(it+2) << std::endl;
        std::cout << findCommonCharPartie2(*it, *(it+1), *(it+2)) << std::endl;
        res += priority(findCommonCharPartie2(*it, *(it+1), *(it+2)));

    }
    return res;
}

int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){
        if (std::strcmp(argv[2], "1")==0){
            for (auto it : {'a', 'z', 'A', 'Z'}){
                std::cout <<it <<':'<< int(it) << "|" <<priority(it) <<std::endl;
            }
        }
    } else {
        std::string path;
        if (std::strcmp(argv[2], "in")==0){
            path = "Input/03in";
        } else if (std::strcmp(argv[2], "ex")==0){
            path = "Input/03ex";
        }
        std::vector<std::string> lines = readFile(path);
        if (std::strcmp(argv[1], "1")==0){
            std::cout << "res = "<<parseJour03partie1(lines) << std::endl;
        } else if (std::strcmp(argv[1], "2")==0){
            //std::cout << "res = "<<parseJour03partie2(lines)<<std::endl;
            parseJour03partie2(lines);
        }
    }
}