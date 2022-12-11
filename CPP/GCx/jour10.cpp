#include <cstring>
#include <string>
#include <vector>
#include "common.h"
#include <deque>
#include <set>

std::deque<std::pair<std::string, int>> get_instructions(std::vector<std::string> lines){
    std::deque<std::pair<std::string, int>> res;
    for(auto l : lines){
        if (l.substr(0, 4)=="noop"){
            res.push_back({l.substr(0, 4), 0});
        } else {
            res.push_back({l.substr(0, 4), std::stoi(l.substr(5, std::string::npos))});
        }
    }
    return res;
}

int jour10partie1(std::deque<std::pair<std::string, int>> instructions){
    int cycle = 1;
    int x = 1;
    int res = 0;
    std::set<int> steps{20, 60, 100, 140, 180, 220};
    while (!instructions.empty() && cycle < 221 )
    {
        std::pair<std::string, int> instr = instructions.front();
        instructions.pop_front();
        if (instr.first=="noop"){
            cycle++;
            if (((cycle-1)%40)+1==20){
                std::cout << cycle << " : res += "<< x*cycle<<" -> "<<res+x*cycle<<std::endl; 
                res+=x*cycle;
            }
        } else if (instr.first == "addx"){
            cycle++;
            if (((cycle-1)%40)+1==20){
                std::cout << cycle << " : res += "<< x*cycle<<" -> "<<res+x*cycle<<std::endl; 
                res+=x*cycle;
            }
            cycle++;
            x+=instr.second;
            if (((cycle-1)%40)+1==20){
                std::cout << cycle << " : res += "<< x*cycle<<" -> "<<res+x*cycle<<std::endl; 
                res+=x*cycle;
            }
        }
    }
    return res;
}

void draw_pixel(int& crt, int position){
    std::cout << ((position-1 <= crt && crt<=position+1) ? '#' : '.');
    // std::cout << "crt = "<<crt <<" & pos = "<<position;
    // if (position-1 <= crt && crt <= position+1){
    //     std::cout << " : #"<<std::endl;
    // } else {
    //     std::cout << " : ."<<std::endl;
    // }
    crt++;
    if (crt % 40 == 0){
        crt-=40;
        // std::cout << "crt ="<<crt<<" : std::endl"<<std::endl;
        std::cout << std::endl;
    } 
}

void jour10partie2(std::deque<std::pair<std::string, int>> instructions){
    int crt = 0;
    int x = 1;
    while (!instructions.empty() && crt <= 240){
        auto instr = instructions.front();
        instructions.pop_front();
        if (instr.first == "noop"){
            draw_pixel(crt, x);
        }
        else if (instr.first == "addx"){
            draw_pixel(crt, x);
            draw_pixel(crt, x);
            x+=instr.second;
        }
    }
}

int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){
        
    } else{
        std::string path;
        if (argc==3 && std::strcmp(argv[2], "in")==0){
            path = "Input/10in";
        } else if (std::strcmp(argv[2], "ex")==0){
            path = "Input/10ex";
        }
        std::vector<std::string> lines = readFile(path);
        auto instructions = get_instructions(lines);
        if (argc==3 && std::strcmp(argv[1], "1")==0){
            std::cout << "Res = "<<jour10partie1(instructions)<<std::endl;
        } else if (argc==3 && std::strcmp(argv[1], "2")==0){
            jour10partie2(instructions);
        }
    } 
    return 0;
}