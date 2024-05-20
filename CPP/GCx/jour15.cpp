#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include "common.h"
struct Sonde{
    int x_sonde;
    int y_sonde;
    int x_balise;
    int y_balise;
    int distance;

    Sonde(std::string line);

    std::pair<int,int> get_horizontal_intervals(int y);

    std::pair<int, int> get_vertical_intervals(int x);
};

inline std::ostream& operator<<(std::ostream& os, const Sonde s){
    os << "Sonde : "<<s.x_sonde<<','<<s.y_sonde<<"; balise : "<<s.x_balise<<","<<s.y_balise << "; distance "<<s.distance;
    return os;
}

Sonde::Sonde(std::string line){
    int i1 = line.find("x=")+2;
    int i2 = line.find(", y=")+4;
    x_sonde = std::stoi(line.substr(i1, i2-i1-4));
    // std::cout << line.substr(i1, i2-i1-4) <<std::endl;
    int i3 = line.find(":");
    y_sonde = std::stoi(line.substr(i2,i3-i2));
    // std::cout << line.substr(i2, i3-i2)<<std::endl;
    int i4 = line.find("x=", i3)+2;
    int i5 = line.find(", y=", i4)+4;
    x_balise = std::stoi(line.substr(i4, i5-i4-4));
    y_balise = std::stoi(line.substr(i5, std::string::npos));

    distance = std::abs(x_sonde - x_balise)+std::abs(y_balise-y_sonde);
}

std::pair<int,int> Sonde::get_horizontal_intervals(int y){
    int delta = distance - std::abs(y-y_sonde);
    int xmin = x_sonde - delta;
    int xmax = x_sonde + delta;
    return {xmin, xmax}; 
}

std::pair<int, int> Sonde::get_vertical_intervals(int x){
    int delta = distance - std::abs(x-x_sonde);
    int ymin = y_sonde - delta;
    int ymax = y_sonde + delta;
    return {ymin, ymax};
}

void test1(){
    Sonde s1{"Sensor at x=24, y=10: closest beacon is at x=28, y=7"};
    auto res = s1.get_horizontal_intervals(6);
    std::cout << res.first << ","<<res.second<<std::endl;

    Sonde s2{"Sensor at x=11, y=9: closest beacon is at x=11, y=10"};
    auto res2 = s2.get_horizontal_intervals(6);
    std::cout << res2.first <<","<<res2.second<<std::endl;
}

std::vector<std::pair<int, int>> get_partition(std::vector<std::pair<int, int>> intervals){
    std::sort(intervals.begin(), intervals.end(), [](std::pair<int, int> a, std::pair<int, int> b){
        return a.first < b.first;
    });
    auto it = intervals.begin();
    std::vector<std::pair<int, int>> res{*it};
    for (it = intervals.begin()+1; it != intervals.end(); it++){
        if (res.back().second < it->first){
            if (it->first == res.back().second+1){
                (res.end()-1)->second = it->second;
            } else {
                res.push_back(*it);
            }
        } else if (res.back().second < it->second) {
            (res.end()-1)->second = it->second;
        }
    }
    return res;
}

int jour15partie1(std::vector<std::string> lines, int y){
    std::vector<Sonde> sondes;
    std::vector<std::pair<int, int>> intervals;
    std::set<int> position_beacon_on_row{};
    for (auto line : lines){
        auto s = Sonde{line};
        sondes.push_back(s);
        std::pair<int, int> interval = s.get_horizontal_intervals(y);
        if (s.y_balise == y){
            position_beacon_on_row.insert(s.y_balise);
        }
        if (interval.first <= interval.second){
            intervals.push_back(interval);
            std::cout << s <<" -> " << interval.first <<","<<interval.second<<std::endl;
        }
        
    }
    std::vector<std::pair<int,int>> partition = get_partition(intervals); 

    int size = 0;
    for(auto it : partition){
        std::cout << it.first << ","<<it.second<<std::endl;
        size += it.second-it.first+1;
    }

    return size-position_beacon_on_row.size();
}

/**
 * @brief 
 * 
 * @param x the value to search for 
 * @param partitions an list of disjoint intervals sorted by ascending order. Each interval represents a point where a beacon cannot be.  
 * @return true if x is not in an interval of impossible values 
 * @return false if x is impossible (i.e. contained in an interval);
 */
bool    check_if_possible(int x, std::vector<std::pair<int, int>> partitions){
    for (auto it : partitions){
        if (x < it.first){
            return true;
        } else if (x <= it.second){
            return false;
        }
    }
    return true;
}

long jour15partie2(std::vector<std::string> lines, int zone_max){
    std::vector<Sonde> sondes;
    // std::vector<std::vector<std::pair<int,int>>> intervals_x;
    // std::vector<std::vector<std::pair<int,int>>> intervals_y;

    std::vector<std::vector<std::pair<int,int>>> intervals_x( zone_max+1 , std::vector<std::pair<int, int>> (0, {0,0}));
    std::vector<std::vector<std::pair<int,int>>> intervals_y( zone_max+1 , std::vector<std::pair<int, int>> (0, {0,0}));

    for (auto l : lines){
        std::cout << l <<std::endl;
        sondes.push_back(Sonde{l});
    }

    std::vector<int> possible_rows;
    std::vector<int> possible_columns;

    for (int i = 0; i <= zone_max; i++){
        std::vector<std::pair<int, int>> temp_x;
        std::vector<std::pair<int, int>> temp_y;
        for (auto s : sondes){
            auto temp_sonde_x = s.get_vertical_intervals(i);
            auto temp_sonde_y = s.get_horizontal_intervals(i);
            if (temp_sonde_x.first <= temp_sonde_x.second){
                temp_x.push_back(temp_sonde_x);
            }
            if (temp_sonde_y.first<= temp_sonde_y.second){
                temp_y.push_back(temp_sonde_y);
            }
        }
        intervals_x[i] = get_partition(temp_x);
        intervals_y[i] = get_partition(temp_y);

        if (!(intervals_x[i].size() == 1 && intervals_x[i][0].first <= 0 && intervals_x[i][0].second > zone_max)){
            std::cout << "Valid ! :";
            possible_columns.push_back(i);
            for (auto it : intervals_x[i]){
                std::cout <<"[" <<it.first << ","<<it.second<<"],";
            }
            std::cout << std::endl;
        }
        // } else {
        //     std::cout << "Invalid ! : ";
        // }

        if (!(intervals_y[i].size() == 1 && intervals_y[i][0].first < 0 && intervals_y[i][0].second > zone_max)){
            possible_rows.push_back(i);
            std::cout << "Valid ! :";
            for (auto it : intervals_y[i]){
                std::cout <<"[" <<it.first << ","<<it.second<<"],";
            }
            std::cout << std::endl;
        }
    }

    for (int x : possible_columns){
        for (int y : possible_rows){
            if (check_if_possible(x, intervals_y[y]) && check_if_possible(y, intervals_x[x])){
                return 4000000l*x+y;
            }
        }
    }
    std::cout <<"Pouet"<<std::endl;
    return 10;
}

int main(int argc, char** argv){
    if (argc ==3 && std::strcmp(argv[1], "test")==0){
        test1();
    } else {
        if (argc == 3 && std::strcmp(argv[1], "1")==0){        
            std::string path;
            int y = 0;
            if (argc == 3 && std::strcmp(argv[2], "ex")==0){
                path = "Input/15ex";
                y = 10;
            } else if (argc == 3 && std::strcmp(argv[2],"in")==0){
                path = "Input/15in";
                y = 2000000;
            }
            std::vector<std::string> lines = readFile(path);
            int res = jour15partie1(lines, y);
            std::cout << "Res partie 1 = "<<res<<std::endl;
        } else if (argc==3 && std::strcmp(argv[1], "2")==0){
            std::string path;
            int zone_max = 0;
            if (argc == 3 && std::strcmp(argv[2], "ex")==0){
                path = "Input/15ex";
                zone_max = 20;
            } else if (argc == 3 && std::strcmp(argv[2],"in")==0){
                path = "Input/15in";
                zone_max = 4000000;
            }
            std::vector<std::string> lines = readFile(path);
            long res = jour15partie2(lines, zone_max);
            std::cout << "Res partie 2 = "<<res<<std::endl;
        }
    }
}