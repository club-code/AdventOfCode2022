#include "common.h"
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
int jour06partie1(std::string line){
    std::unordered_map<char, int> content;
    for (int i = 0; i < 4; i++){
        content[line[i]]++;
    }
    if (content[line[0]]+content[line[1]]+content[line[2]]+content[line[3]]!=4)
    for (size_t j = 4; j < line.length(); j++ ){
        content[line[j-4]]--;
        content[line[j]]++;
        if (content[line[j]]+content[line[j-1]]+content[line[j-2]]+content[line[j-3]]==4){
            return j+1;
        }
    }
    return 1;
}

int main (int argc, char** argv){
    if (argc==3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (std::strcmp(argv[2], "in")==0){
            path = "Input/06in";
        } else if (std::strcmp(argv[2], "ex")==0){
            path = "Input/06ex";
        }
        
        auto lines = readFile(path);
        if (std::strcmp(argv[1], "1")==0){
            for (auto l : lines){
                int res = jour06partie1(l);
                std::cout << l << std::endl;
                std::cout << "Res = "<< res<<std::endl <<std::endl;
            } 
        }
    }
}