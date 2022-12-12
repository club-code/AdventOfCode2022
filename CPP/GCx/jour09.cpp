#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include "common.h"

void apply_move(std::pair<int, int> &head, std::pair<int, int> &tail, std::pair<int, int> direction)
{
    // std::cout << head.first<<','<<head.second<<" & "<<tail.first <<","<<tail.second<<" --"<<direction.first<<","<<direction.second<<"->     ";
    head.first += direction.first;
    head.second += direction.second;
    if (std::max(std::abs(head.first - tail.first), std::abs(head.second - tail.second)) > 1)
    {
        tail.first = head.first - direction.first;
        tail.second = head.second - direction.second;
    }
    // std::cout << head.first<<','<<head.second<<" & "<<tail.first <<","<<tail.second<<std::endl;
}

int jour09partie1(std::vector<std::pair<std::pair<int, int>, int>> moves)
{
    std::pair<int, int> head{0, 0};
    std::pair<int, int> tail{0, 0};
    std::set<std::pair<int, int>> seen{{0, 0}};
    for (auto move : moves)
    {
        // std::cout << "Move "<<move.first.first<<','<<move.first.second<<" "<<move.second<<std::endl;
        for (int i = 0; i < move.second; i++)
        {
            apply_move(head, tail, move.first);
            // std::cout << tail.first<<","<<tail.second<<std::endl;
            seen.insert(tail);
        }
    }
    std::cout << "Res = " << seen.size() << std::endl;
    return 1;
}

void print_rope(std::vector<std::pair<int,int>> rope){
    for (int i = 9; i > 0; i--){
        std::cout << '(' << rope[i].first <<','<<rope[i].second<<')'<<"->";
    }
    std::cout << '('<<rope[0].first<<','<<rope[0].second<<')'<<std::endl;
}

void apply_move(std::vector<std::pair<int, int>> &rope, std::pair<int, int> direction)
{
    rope[0].first += direction.first;
    rope[0].second += direction.second;

    for (int i = 1; i < rope.size(); i++)
    {
        if (std::max(std::abs(rope[i-1].first-rope[i].first), std::abs(rope[i-1].second-rope[i].second))>1){
            // std::cout << "==="<<std::endl; 
            // std::cout <<"i = "<<i<<": "<<'('<<rope[i].first<<','<<rope[i].second<<") & ("<<rope[i-1].first<<','<<rope[i-1].second<<')';
            if (std::abs(rope[i].first-rope[i-1].first)>1 && rope[i].second == rope[i-1].second){
                rope[i].first += (rope[i - 1].first - rope[i].first) / (std::abs(rope[i - 1].first - rope[i].first));
            } else if (std::abs(rope[i].second-rope[i-1].second)>1 && rope[i].first == rope[i-1].first){
                rope[i].second += (rope[i - 1].second - rope[i].second) / (std::abs(rope[i - 1].second - rope[i].second));
            } else if ((std::abs(rope[i].first-rope[i-1].first)>1)||(std::abs(rope[i].second-rope[i-1].second))>1){
                rope[i].first += (rope[i - 1].first - rope[i].first) / (std::abs(rope[i - 1].first - rope[i].first));
                rope[i].second += (rope[i - 1].second - rope[i].second) / (std::abs(rope[i - 1].second - rope[i].second));
            }
            // std::cout << "-> ("<<rope[i].first<<','<<rope[i].second<<')'<<std::endl;
        }
    }
}

int jour09partie2(std::vector<std::pair<std::pair<int, int>, int>> moves)
{
    std::vector<std::pair<int, int>> rope(10);
    std::set<std::pair<int, int>> seen{{0, 0}};
    for (auto move : moves)
    {
        for (int i = 0; i < move.second; i++)
        {
            apply_move(rope, move.first);
            seen.insert(rope[9]);
            // print_rope(rope);
        }
    }
    std::cout << "Res =" << seen.size() << std::endl;
    return seen.size();
}

std::vector<std::pair<std::pair<int, int>, int>> get_moves(std::vector<std::string> lines)
{
    std::vector<std::pair<std::pair<int, int>, int>> moves;
    for (auto l : lines)
    {
        std::pair<int, int> dir;
        switch (l[0])
        {
        case 'R':
            dir = {0, 1};
            break;
        case 'L':
            dir = {0, -1};
            break;
        case 'U':
            dir = {1, 0};
            break;
        case 'D':
            dir = {-1, 0};
            break;
        }
        moves.push_back({dir, std::stoi(l.substr(2, std::string::npos))});
        std::cout << l << " : " << moves.back().first.first << "," << moves.back().first.second << " - " << moves.back().second << std::endl;
    }
    return moves;
}

int main(int argc, char **argv)
{
    std::string path;

    if (argc == 3 && std::strcmp(argv[1], "test") == 0)
    {
        if (std::strcmp(argv[2], "1")==0){
            path = "Input/09test1";
            std::vector<std::string> moves = readFile(path);
            auto parsed_moves=get_moves(moves);
            jour09partie2(parsed_moves);
        } else if (std::strcmp(argv[2], "2")==0){
            std::cout <<"0+(0-0)/(0-0) =" <<0+(0-0)/(0-0)<<std::endl;
            std::cout <<"0+(2-0)/(std::abs(2-0)) ="<<0+(2-0)/(std::abs(2-0))<<std::endl;
        }
    }
    else
    {
        if (argc == 3 && std::strcmp(argv[1], "1") == 0)
        {
            if (argc == 3 && std::strcmp(argv[2], "in") == 0)
            {
                path = "Input/09in";
            }
            else if (argc == 3 && std::strcmp(argv[2], "ex") == 0)
            {
                path = "Input/09ex";
            }
            std::vector<std::string> moves = readFile(path);
            auto parsed_moves = get_moves(moves);
            jour09partie1(parsed_moves);
        }
        if (argc == 3 && std::strcmp(argv[1], "2") == 0)
        {
            if (argc == 3 && std::strcmp(argv[2], "in") == 0)
            {
                path = "Input/09in";
            }
            else if (argc == 3 && std::strcmp(argv[2], "ex") == 0)
            {
                path = "Input/09ex2";
            }
            std::vector<std::string> moves = readFile(path);
            auto parsed_moves = get_moves(moves);
            jour09partie2(parsed_moves);
        }
    }
}