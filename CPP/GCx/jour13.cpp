#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include "common.h"


std::vector<std::pair<std::string, std::string>> get_pairs(std::vector<std::string> lines){
    int i = 0;
    std::vector<std::pair<std::string, std::string>> res;
    while (i < lines.size()){
        res.push_back({lines[i], lines[i+1]});
        i+=3;
    }
    return res;
}

std::vector<std::string> split_string(std::string str){
    // std::cout << "Splitting "<<str<<std::endl;
    int begin = 1;
    int curseur = 1;
    int level = 1;
    std::vector<std::string> res;
    if (str=="[]"){
        return res;
    }
    while (level > 0){
        if (str[curseur]==',' && level == 1){
            // std::cout << str.substr(begin, curseur-begin) << std::endl;
            res.push_back(str.substr(begin, curseur-begin));
            begin = curseur+1;
            curseur++;
        } else if (str[curseur] == ']' && level == 1){
            // std::cout << str.substr(begin, curseur-begin) << std::endl;
            res.push_back(str.substr(begin, curseur-begin));
            return res;
        } else if (str[curseur] == '['){
            level++;
            curseur++;
        } else if (str[curseur]==']'){
            level--;
            curseur++;
        } else {
            curseur++;
        }
    }

    return res;
}

int check_order(std::string left, std::string right){
    if (left[0]!='[' && right[0]!='['){
        if (std::stoi(left) < std::stoi(right)){
            std::cout << "1. Comparing " << left << " and "<<right<<" : "<<" OK;"<<std::endl;
            return 1;
        } else if (std::stoi(left) > std::stoi(right)){
            std::cout << "2. Comparing " << left << " and "<<right<<" : "<<" Not OK;"<<std::endl;
            return -1;
        } else {
            std::cout << "3. Comparing " << left << " and "<<right<<" : "<<" Equal;"<<std::endl;
            return 0;
        }
    }
    else if (left[0]=='[' && right[0]!='['){
        int aux_1 = check_order(left, '['+right+']');
        return aux_1;
    } else if (left[0]!='[' && right[0]=='['){
        int aux_2 =  check_order('['+left+']', right);
        return aux_2;
    } else {
        std::cout << "4. Comparing "<<left<<" and "<<right<<std::endl;
        std::vector<std::string> vec_left = split_string(left);
        std::vector<std::string> vec_right = split_string(right);
        auto it_left = vec_left.begin();
        auto it_right = vec_right.begin();

        while (it_left!=vec_left.end() && it_right!=vec_right.end()){
            std::cout << "before 5 :"<<std::endl;
            int res_1 = check_order(*it_left, *it_right);
            std::cout << "5. Comparison of "<<*it_left<<" & "<<*it_right<<" = "<<res_1<<std::endl;
            if (res_1 != 0){
                return res_1;
            }
            it_left++;
            it_right++;
        }

        if (it_left == vec_left.end() && it_right != vec_right.end()){
            std::cout <<"6."<< left << " ran out before "<<right<<" : Ok"<<std::endl;
            return 1;
        } else if (it_left != vec_left.end() && it_right == vec_right.end()){
            std::cout << "7."<< left << " ran out after "<<right << ": Not Ok"<<std::endl;
            return -1;
        } else {
            std::cout << "8."<< left << " == "<<right <<std::endl;
            return 0;
        }
        
    }
}

int jour13partie1(std::vector<std::pair<std::string, std::string>> pairs){
    int i = 1;
    int res = 0;
    for (auto it : pairs){
        int aux = check_order(it.first, it.second);
        if (aux == 1){
            std::cout << it.first <<" and "<<it.second<<" "<<aux<<" : OK"<<std::endl<<std::endl;
            res+=i;
        } else {
            std::cout << it.first <<" and "<<it.second<<" " << aux<<" : Not OK"<<std::endl<<std::endl;
        }
        i++;
    }
    std::cout << "Partie 1 ="<<res;
    return res;
}

std::vector<std::string> parse_partie_2(std::vector<std::string> lines){
    int i = 0;
    std::vector<std::string> res;
    while (i < lines.size()){
        res.push_back(lines[i]);
        res.push_back(lines[i+1]);
        i+=3;
    }
    res.push_back("[[2]]");
    res.push_back("[[6]]");
    return res;
}

int main(int argc, char** argv){
    if (argc == 3 && std::strcmp(argv[1], "test")==0){
        split_string("[1,[2,[3,[4,[5,6,7]]]],8,9]");
    } else {
        std::string path;
        if (argc == 3 && std::strcmp(argv[2], "in")==0){
            path = "Input/13in";
        } else if (argc == 3 && std::strcmp(argv[2], "ex")==0){
            path = "Input/13ex";
        } 

        std::vector<std::string> lines = readFile(path);
        
        if (argc == 3 && std::strcmp(argv[1], "1")==0){
            std::vector<std::pair<std::string, std::string>> pairs = get_pairs(lines);

            for (auto it : pairs){
                std::cout << it.first<<" | "<<it.second<<std::endl;
            }

            jour13partie1(pairs);
        } else if (argc ==3 && std::strcmp(argv[1], "2")==0){
            auto all_lines = parse_partie_2(readFile(path));
            std::sort(all_lines.begin(), all_lines.end(), [](std::string a, std::string b){
                return (check_order(a, b)==1);
            });
            int i = 1;
            int res = 1;
            for (auto it : all_lines){
                if (it == "[[2]]" || it=="[[6]]"){
                    res*=i;
                }
                std::cout <<i <<" : "<< it <<std::endl;
                i++;
            }
            std::cout << "Res partie 2 ="<<res<<std::endl;
        }
    }
}