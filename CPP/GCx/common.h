#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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