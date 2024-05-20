#include "jour04.h"
#include "common.h"
#include <cstring>
#include <string>
#include <iostream>

Range::Range(std::string str){
    min = std::stoi(str.substr(0, str.find('-')));
    max = std::stoi(str.substr(str.find('-')+1, std::string::npos));

}

bool contains(Range r1, Range r2){
    return (r1.min <= r2.min && r2.max <= r1.max) || (r2.min <= r1.min && r1.max <= r2.max);
}

bool do_overlap(Range r1, Range r2){
    return (r1.min <= r2.max && r2.max <= r1.max) || (r2.min <= r1.max && r1.max <= r2.max);
}

int jour04partie1(std::vector<std::string> lines){
    int count =0;
    for(auto l : lines){
        std::string s1 = l.substr(0, l.find(','));
        std::string s2 = l.substr(l.find(',')+1, std::string::npos);
        // std::cout << Range(s1)<<" & "<<Range(s2)<<std::endl;
        if (contains(Range(s1), Range(s2))){
            count++;
        }
    }
    return count;
}

int jour04partie2(std::vector<std::string> lines){
    int count = 0;
    for (auto l : lines){
        std::string s1 = l.substr(0, l.find(','));
        std::string s2 = l.substr(l.find(',')+1, std::string::npos);
        if (do_overlap(Range(s1), Range(s2))){
            count++;
        }
    }
    return count;
}

void test01(){
    auto lines = readFile("Input/04test01");
    int count = 0;
    for (auto l : lines){
        std::string s1 = l.substr(0, l.find(','));
        std::string s2 = l.substr(l.find(',')+1, std::string::npos);
        if (do_overlap(Range(s1), Range(s2))){
            std::cout << "Don't overlap : ";
            count++;
        } else {
            std::cout << "Do overlap : ";
        }
        std::cout <<l<<std::endl;
    }
    std::cout << "count = "<<count<<std::endl;

}


int main(int argc, char** argv){

    if (argc == 3 && std::strcmp(argv[1], "test")==0){
        if (std::strcmp(argv[2], "1")==0){
            test01();
        }
    } else {
        std::string path;
        if (std::strcmp(argv[2], "ex") == 0){
            path = "Input/04ex";
        } else if (std::strcmp(argv[2], "in")==0){
            path = "Input/04in";
        }
        auto lines = readFile(path);
        if (std::strcmp(argv[1], "1")==0){
            int res = jour04partie1(lines);
            std::cout << "Res = "<<res<<std::endl;
        } else if (std::strcmp(argv[1], "2")==0){
            int res = jour04partie2(lines);
            std::cout << "Res = "<<res<<std::endl;
        }
    }
}