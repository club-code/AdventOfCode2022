#include "common.h"
#include "jour05.h"
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <stack>
#include <queue>
std::vector<std::stack<char>> get_stacks(std::vector<std::string> lines, int delimitation){
    size_t it = 1;
    std::vector<std::stack<char>> stacks;
    while(it < lines[delimitation-1].size()-1){
        stacks.push_back(std::stack<char>());
        it+=4;
    }
    
    for(int i = delimitation-2; i >= 0; i--){
        int c = 0;
        for (size_t j = 1; j <= lines[i].length()-1; j+=4){
            std::cout << lines[i][j];
            if (lines[i][j]!=' '){
                stacks[c].push(lines[i][j]);
            }
            c++;
        }
        std::cout << std::endl;
    }
    return stacks;
}

std::queue<std::vector<int>> get_instructions(std::vector<std::string> lines, int delimitation){
    std::queue<std::vector<int>> res;
    for (size_t i = delimitation+1; i < lines.size(); i++){
        int instr1 = std::stoi(lines[i].substr(4, lines[i].find(" from ")-1));
        int instr2 = std::stoi(lines[i].substr(lines[i].find(" from ")+6, lines[i].find(" to ")));
        int instr3 = std::stoi(lines[i].substr(lines[i].find(" to ")+4, std::string::npos));
        res.push({instr1, instr2, instr3});
    }
    return res;
}

void apply_instruction_partie_1(std::vector<std::stack<char>>& stacks, std::vector<int> instr){
    int from = instr[1]-1;
    int to = instr[2]-1;
    for (int i_crates = 0; i_crates < instr[0]; i_crates++){
        stacks[to].push(stacks[from].top());
        stacks[from].pop();
    }
}

void apply_instruction_partie_2(std::vector<std::stack<char>>& stacks, std::vector<int> instr){
    int from = instr[1]-1;
    int to = instr[2]-1;
    std::stack<char> buffer;
    for (int i_crates = 0; i_crates<instr[0]; i_crates++){
        buffer.push(stacks[from].top());
        stacks[from].pop();
    }
    while(!buffer.empty()){
        stacks[to].push(buffer.top());
        buffer.pop();
    }
}

std::string jour05partie1(std::vector<std::string> lines){
    int delimitation = 0;
    for (size_t i = 0; i < lines.size(); i++){
        if (lines[i].length() < 2){
            delimitation = i;
            break;
        }
    }

    auto stacks = get_stacks(lines, delimitation);

    auto instr = get_instructions(lines, delimitation);

    while (!instr.empty()){
        apply_instruction_partie_1(stacks, instr.front());
        instr.pop();
    }
    std::cout << "==== Res ==="<<std::endl;
    for (auto it : stacks){
        std::cout << it.top();
    }
    std::cout << std::endl;
    return "null";
}

std::string jour05partie2(std::vector<std::string> lines){
    int delimitation = 0;
    for (size_t i = 0; i < lines.size(); i++){
        if (lines[i].length() < 2){
            delimitation = i;
            break;
        }
    }

    auto stacks = get_stacks(lines, delimitation);

    auto instr = get_instructions(lines, delimitation);

    while (!instr.empty()){
        apply_instruction_partie_2(stacks, instr.front());
        instr.pop();
    }
    std::cout << "==== Res ==="<<std::endl;
    for (auto it : stacks){
        std::cout << it.top();
    }
    std::cout << std::endl;
    return "null";
}

int main (int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (std::strcmp(argv[2], "ex")==0){
            path = "Input/05ex";
        } else if (std::strcmp(argv[2], "in")==0){
            path = "Input/05in";
        }

        auto lines = readFile(path);
        if (std::strcmp(argv[1], "1")==0){
            jour05partie1(lines);
        } else if (std::strcmp(argv[1], "2")==0){
            jour05partie2(lines);
        }
    }
}