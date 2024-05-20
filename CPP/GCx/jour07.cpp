#include <iostream>
#include <cstring>
#include <string>
#include <unordered_map>
#include "common.h"
#include <algorithm>

int archive(std::vector<std::string> lines){
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
                std::cout << dir_sizes[lines[j].substr(lines[j].find("dir ")+4, std::string::npos)] <<std::endl;
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

struct Directory{
    std::string name;
    Directory* parent;
    std::unordered_map<std::string, Directory*> children;
    std::unordered_map<std::string, int> files;
    int size = 0;

    Directory(){}

    Directory(Directory* parent): parent{parent}{}
    
    Directory(std::string name){
        this->name = name;
    }

    Directory(Directory* parent, std::string name){
        this->parent = parent;
        this->name = name; 
    }

    int set_size(){
        if (size != 0){
            return size;
        } else {
                
            int res = 0;
            for (auto it : children){
                res+=it.second->set_size();
            }
            for (auto it_file : files){
                res+=it_file.second;
            }
            size = res;
            return res;
        }
    }

    int recurse_partie_1(){
        int res = 0;
        for (auto it_children : children){
            res += it_children.second->recurse_partie_1();
        } 
        if (size <= 100000){
            res+=size;
        }
        return res;
    }

    void recurse_partie_2(int minimum_space_required, int& current_min){
        if (minimum_space_required+size>=30000000){
            if (size<current_min){
                current_min = size;
            }
            for (auto it_child : children){
                it_child.second->recurse_partie_2(minimum_space_required, current_min);
            }
        }
    }
};

int get_current_line_size(std::string line, std::unordered_map<std::string, int> dir_sizes){
    if ('0'<=line[0] && line[0]<='9'){
        return std::stoi(line.substr(0, line.find(' ')));
    } else if (line.substr(0, 3) == "dir"){
        return dir_sizes[line.substr(line.find("dir ")+4, std::string::npos)];
    }
    return 0;
}

int jour07(std::vector<std::string> lines){
    Directory root{"/"};
    Directory* current_dir = &root;
    size_t i = 1;
    while (i < lines.size()){
        std::cout <<"Current dir "<<current_dir->name<< ">>"<<lines[i]<<std::endl;
        if (lines[i].substr(0, 7)=="$ cd .."){
            // std::cout <<i <<" cd .." << std::endl;
            current_dir = current_dir->parent;
            i++;
        } else if (lines[i].substr(0, 4)== "$ cd"){
            std::string dest = lines[i].substr(5, std::string::npos);
            // std::cout <<i << " cd ["<<dest<<"]"<<std::endl;
            current_dir = current_dir->children[dest];
            i++;
        } else if (lines[i].substr(0, 4)== "$ ls"){
            i++;
            while (i<lines.size() && lines[i][0]!= '$'){
                if (lines[i].substr(0, 4) == "dir "){
                    std::string key = lines[i].substr(4, std::string::npos);
                    current_dir->children[key] = new Directory{current_dir, key};
                } else {
                    int file_size = std::stoi(lines[i].substr(0, lines[i].find(" ")));
                    std::string file_name = lines[i].substr(lines[i].find(" ")+1, std::string::npos);
                    current_dir->files[file_name] = file_size;  
                }
                i++;
            }
        }
    }
    root.set_size();
    int res1 = root.recurse_partie_1();
    std::cout << "Partie 1 : "<< res1<<std::endl;

    int used_space = root.size;
    int unused_space = 70000000-used_space;
    int current_min = used_space;
    root.recurse_partie_2(unused_space, current_min);

    std::cout << "Partie 2 : "<<current_min<<std::endl;
    return root.recurse_partie_1();
}

int main (int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){
        std::string path = "Input/07test";
        auto lines = readFile(path);
        int res = archive(lines);
        std::cout << "Res = "<<res<<std::endl;
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
            res = archive(lines);
        } else if (std::strcmp(argv[1], "2")==0){
            res = jour07(lines);
        }
        std::cout << "Res = "<<res<<std::endl;
        
    } 
    return 1;
}