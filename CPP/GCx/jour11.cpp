#include <cstring>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <functional>
#include <unordered_map>
#include "common.h"
#include "jour11.h"

std::unordered_map<int, Monkey> parseInput(std::vector<std::string> lines){
    int i = 0;
    std::unordered_map<int, Monkey> monkeys;
    while (i < lines.size()){
        std::cout <<"["<<lines[i].substr(lines[i].find(" ")+1, lines[i].substr(lines[i].find(" ")+1, std::string::npos).find(":"))<<"]"<<std::endl;
        int monkey_num = std::stoi(lines[i].substr(lines[i].find(" ")+1, lines[i].substr(lines[i].find(" ")+1, std::string::npos).find(":")));
        monkeys[monkey_num] = Monkey{lines, i};
        i+=7;
    }
    return monkeys;
} 

void Monkey::throw_item(int worry_level, std::unordered_map<int, Monkey>& monkeys){
    if (worry_level%divisibility_criteria == 0){
        std::cout << " divisible by "<<divisibility_criteria<<" : thrown to "<<monkey_true <<std::endl;
        monkeys[monkey_true].items.push_back(worry_level);
    } else {
        std::cout << " not divisible by "<<divisibility_criteria<<" : thrown to "<<monkey_false<<std::endl;
        monkeys[monkey_false].items.push_back(worry_level);
    }
}

Monkey::Monkey(std::vector<std::string> vec, int first){
    size_t begin = vec[first+1].find(": ")+2;

    items = std::deque<int>();
    while (begin < vec[first+1].size()-1){
        // std::cout << "{"<<vec[first+1].substr(begin, vec[first+1].substr(begin, std::string::npos).find(", "))<<"}";
        items.push_back(std::stoi(vec[first+1].substr(begin, vec[first+1].substr(begin, std::string::npos).find(", ")))); 
        begin = begin+vec[first+1].substr(begin, std::string::npos).find(", ")+2;
    }

    char op_char = vec[first+2][vec[first+2].find("new = old ")+10];
    std::function<int(int, int)> op; 
    if (op_char=='+'){
        op = std::plus<int>();
    } else if (op_char=='*'){
        op = std::multiplies<int>();
    }

    std::string second_arg = vec[first+2].substr(vec[first+2].find("new = old ")+12, std::string::npos);

    if (second_arg=="old"){
        this->function = [op](int i){ return op(i, i);};
    } else {
        int arg = std::stoi(second_arg);
        this->function = [op, arg](int i){ return op(i, arg);};
    }

    // std::cout <<"old"<< op_char <<second_arg<< "->"<< function(5)<<std::endl;  

    divisibility_criteria = std::stoi(vec[first+3].substr(vec[first+3].find("by ")+3, std::string::npos));
    std::cout << "{"<<divisibility_criteria<<"}"<<std::endl;

    monkey_true = std::stoi(vec[first+4].substr(vec[first+4].find("monkey ")+7, std::string::npos));
    monkey_false = std::stoi(vec[first+5].substr(vec[first+5].find("monkey ")+7, std::string::npos));
    std::cout << "{"<<monkey_true<<"}"<<"["<<monkey_false<<"]"<<std::endl;
}

Monkey::Monkey(){};

void Monkey::turn(std::unordered_map<int, Monkey>& monkeys){
    int current_item;
    while(!items.empty()){
        monkey_business++;
        current_item = items.front();
        std::cout << "starting worry : "<<current_item;
        items.pop_front();
        current_item = function(current_item);
        current_item /= 3;
        std::cout << " becomes "<<current_item;
        throw_item(current_item, monkeys);
    }
}

void round(std::unordered_map<int, Monkey>& monkeys){
    for (int i = 0; i < monkeys.size(); i++){
        monkeys[i].turn(monkeys);
    }
}

void jour11partie01(std::unordered_map<int, Monkey> monkeys){
    for (int i = 1; i < 21; i++){
        std::cout << "Round "<<i<<std::endl;
        round(monkeys);
    }
    std::vector<int> res;
    int max1{0}, max2{0};
    for (int i = 0; i < monkeys.size(); i++){
        std::cout << "Monkey "<<i<<" : "<<monkeys[i].monkey_business<<std::endl;
        res.push_back(monkeys[i].monkey_business);
        if (monkeys[i].monkey_business > max1){
            max2 = max1;
            max1 = monkeys[i].monkey_business;
        } else if (monkeys[i].monkey_business > max2){
            max2 = monkeys[i].monkey_business;
        }
    }
    std::cout << "max 1 = "<<max1<<", max2 = "<<max2<<std::endl;
    std::cout << "Res = "<<max1*max2<<std::endl;
}

int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){

    } else {
        std::string path;
        if (argc == 3 && std::strcmp(argv[2], "ex")==0){
            path = "Input/11ex";
        } else if (argc == 3 && std::strcmp(argv[2], "in")==0){
            path = "Input/11in";
        }

        std::vector<std::string> lines = readFile(path);
        auto res = parseInput(lines);
        jour11partie01(res);
    }
}