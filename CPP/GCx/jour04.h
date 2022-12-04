#include <string>
#include <vector>
#include <ostream>
struct Range{
    int min;
    int max;

    Range(std::string);
};

inline std::ostream& operator<<(std::ostream& os, const Range r){
    os << "["<<r.min<<","<<r.max<<"]";
    return os;
} 

int jour04partie1(std::vector<std::string> lines);

int jour04partie2(std::vector<std::string> lines);