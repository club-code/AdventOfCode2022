#include "jour02.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

int jour02partie1(std::string path){
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()){
        throw std::invalid_argument("Could not open the file "+path);
    }
    
    std::string line;
    int score = 0;
    while (std::getline(inputFile, line))
    {
        if ((line[0] == 'A' && line[2]=='X') 
        || (line[0] == 'B' && line[2]=='Y')
        || (line[0] == 'C' && line[2]=='Z')){
            score+=3;
        } else if ((line[0] == 'A' && line[2]=='Y') 
        || (line[0] == 'B' && line[2]=='Z')
        || (line[0] == 'C' && line[2]=='X')){
            score+=6;
        }
        switch (line[2]){
            case 'X':
                score+=1;
                break;
            case 'Y':
                score+=2;
                break;
            case 'Z':
                score+=3;
                break;
        }
    }
    return score;
}

int jour02partie2(std::string path){
    std::fstream inputFile;
    inputFile.open(path, std::ios::in);
    if (!inputFile.is_open()){
        throw std::invalid_argument("Could not open the file "+path);
    }
    
    std::string line;
    int score = 0;
    while (std::getline(inputFile, line))
    {
        switch (line[2]){
            case 'X':
                score+=0;
                break;
            case 'Y':
                score+=3;
                break;
            case 'Z':
                score+=6;
                break;
        }
        /*Pierre*/
        if ((line[0] == 'A' && line[2] == 'Y')
        || (line[0] == 'B' && line[2] == 'X')
        || (line[0] == 'C' && line[2] == 'Z')){
            score+=1;
        } else if ((line[0] == 'A' && line[2] == 'Z')
        || (line[0] == 'B' && line[2] == 'Y')
        || (line[0] == 'C' && line[2] == 'X')){ /*Feuille*/
            score+=2;
        } else { /*Ciseaux*/
            score+=3;
        }
    }
    return score;
}

int main(int argc, char** argv){
    std::string path;
    if (argc!=3){
        std::cerr << "3 argument expected, but "<<argc<<" were given";
        return 1;
    }
    if (std::strcmp(argv[2], "in")==0){
        path = "Input/02in";
    } else if (std::strcmp(argv[2], "ex")==0){
        path = "Input/02ex";
    }

    if (std::strcmp(argv[1], "1")==0){
        std::cout << jour02partie1(path)<<std::endl;
    } else if (std::strcmp(argv[1], "2")==0){
        std::cout << jour02partie2(path)<<std::endl;
    }
    return 0;
}