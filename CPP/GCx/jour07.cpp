#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include "common.h"
#include <algorithm>
int jour07partie1(std::vector<std::string> lines){
    int res = 0;
    std::unordered_map<std::string, int> dir_sizes;
    int i = lines.size()-1;
    while (i>=0){
        int j = i;
        int cur_directory_size = 0;
        //We get every element (dir or file) in that directory and sum up the size;
        while (lines[j].substr(0, 4) != "$ ls"){
            if ('0'<=lines[j][0] && lines[j][0]<='9'){
                cur_directory_size += std::stoi(lines[j].substr(0, lines[j].find(' ')));
            } else if (lines[j].substr(0, 3) == "dir"){
                cur_directory_size += dir_sizes[lines[j].substr(lines[j].find("dir ")+4, std::string::npos)];
            }
            j--;
        }        

        // We get the current directory name from the line "$ cd [directory_name]" and update its total weight;
        std::string directory_name = lines[j-1].substr(lines[j-1].find("cd ")+3, std::string::npos);
        dir_sizes[directory_name] = cur_directory_size;
        if (cur_directory_size <= 100000){
            res+=cur_directory_size;
        }
        //Skipping the ls and cd lines for the current directory;
        j-=2;
        //Skipping the "$ cd .." lines which are useless to us;
        while (j >= 0 && lines[j].substr(0,7) == "$ cd .."){
            j--;
        }
        i = j;
    }
    return res;
}


int get_current_line_size(std::string line, std::unordered_map<std::string, int> dir_sizes){
    if ('0'<=line[0] && line[0]<='9'){
        return std::stoi(line.substr(0, line.find(' ')));
    } else if (line.substr(0, 3) == "dir"){
        return dir_sizes[line.substr(line.find("dir ")+4, std::string::npos)];
    }
    return 0;
}

int jour07partie2(std::vector<std::string> lines){
    std::unordered_map<std::string, int> dir_sizes;
    int i = lines.size()-1;
    while (i>=0){
        int j = i;
        int cur_directory_size = 0;
        //We get every element (dir or file) in that directory and sum up the size;
        while (lines[j].substr(0, 4) != "$ ls"){
            cur_directory_size += get_current_line_size(lines[j], dir_sizes);
            j--;
        }        

        // We get the current directory name from the line "$ cd [directory_name]" and update its total weight;
        std::string directory_name = lines[j-1].substr(lines[j-1].find("cd ")+3, std::string::npos);
        std::cout << "["<<directory_name<<"]"<<std::endl;
        dir_sizes[directory_name] = cur_directory_size;
        std::cout << "Dir "<<directory_name<<" & size = "<<cur_directory_size << std::endl;

        //Skipping the ls and cd lines for the current directory;
        j-=2;
        //Skipping the "$ cd .." lines which are useless to us;
        while (j >= 0 && lines[j].substr(0,7) == "$ cd .."){
            j--;
        }
        i = j;
    }
    int available_space = 70000000-dir_sizes["/"];
    int current_min_size = dir_sizes["/"];
    std::cout << "Current_min_size "<<current_min_size<<std::endl;
    for (auto it : dir_sizes){
        std::cout << it.first << " "<<it.second<<std::endl;
        if (available_space+it.second >= 30000000 && it.second < current_min_size){
            current_min_size = it.second;
        }
    }
    std::cout << "available_space = "<<available_space<<" and current min size = "<<current_min_size<<std::endl;
    return current_min_size;
    // return current_min_size;
}

int main (int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[2], "test")==0){

    } else {
        std::string path;
        
        if (std::strcmp(argv[2], "in")==0){
            path = "Input/07in";
        } else if (std::strcmp(argv[2], "ex")==0){
            path = "Input/07ex";
        }

        auto lines = readFile(path);
        int res = 0;
        if (std::strcmp(argv[1], "1")==0){
            res = jour07partie1(lines);
        } else if (std::strcmp(argv[1], "2")==0){
            res = jour07partie2(lines);
        }
        std::cout << "Res = "<<res<<std::endl;
        
    } 
    return 1;
}