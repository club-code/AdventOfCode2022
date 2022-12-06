#include "common.h"
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>

bool check(std::string line, std::unordered_map<char, int> content, int current, int message_length){
    for (int i = current - message_length + 1;  i <= current; i++){
        if (content[line[i]]!=1){
            return false;
        }
    }
    return true;
}

std::unordered_map<char, int> init(std::string line, int message_length){
    std::unordered_map<char, int> content;
    for (int i = 0; i < message_length; i++){
        content[line[i]]++;
    }
    return content;
}

int jour06partie1(std::string line){
    auto content = init(line, 4);
    if (content[line[0]]+content[line[1]]+content[line[2]]+content[line[3]]!=4)
    for (size_t j = 4; j < line.length(); j++ ){
        content[line[j-4]]--;
        content[line[j]]++;
        if (check(line, content, j, 4)){
            std::cout << "True : "<< j +1 <<std::endl;
        }
        if (content[line[j]]+content[line[j-1]]+content[line[j-2]]+content[line[j-3]]==4){
            std::cout << line[j-3]<<line[j-2]<<line[j-1]<<line[j]<<std::endl;
            return j+1;
        }
    }
    return 1;
}

int jour06(std::string line, int message_length){
    auto content = init(line, message_length);
    for (size_t j = message_length; j < line.length(); j++){
        content[line[j-message_length]]--;
        content[line[j]]++;
        if (check(line, content, j, message_length)){
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
        int message_length = 4;
        if (std::strcmp(argv[1], "1")==0){ 
            message_length = 4;
        } else if (std::strcmp(argv[1], "2")==0){
            message_length = 14;
        }
        for (auto l : lines){
            int res = jour06(l, message_length);
            std::cout << l << std::endl;
            std::cout << "Res = "<< res<<std::endl <<std::endl;
        } 
    }
}