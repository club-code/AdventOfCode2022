#pragma once

#ifndef COMMON
#define COMMON
#endif 

#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>

#include <algorithm>
#include <functional>
#include <utility>
#include <numeric>
#include <cmath>
#include <tgmath.h>
#include <ranges>

#include <cstdint>
#include <string>
#include <string_view>
#include <cstring>
#include <cctype>
#include <vector>
#include <bitset>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <queue>
#include <iterator>

#define fwd(x) static_cast<decltype(x)&&>(x)

#define lift(f) [](auto... x) { return f(x...); }

template<typename Callable>
using return_type_of_t = 
    typename decltype(std::function{std::declval<Callable>()})::result_type;

// Note to self : for accurate results do a cache run before part one.
template <typename F, typename... Ts>
auto profile(std::string_view msg, F f, Ts... as) {
    const auto start = std::chrono::high_resolution_clock::now();
    auto result = f(fwd(as)...);
    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << msg << " took : " << (end - start).count() << " ns\n";
    return result;
}

[[nodiscard]] std::vector<std::string> readFile(std::filesystem::path filename) {
    std::ifstream inputFile;
    inputFile.open(filename);
    if (!inputFile.is_open()) throw std::runtime_error("Could not open file : " + filename.string());

    std::vector<std::string> out;
    std::string bufferedString;

    while(std::getline(inputFile, bufferedString)) {
        out.push_back(bufferedString);
    }
    return out;
}

std::vector<std::string> split_string(std::string s, std::string delim) {
    std::vector<std::string> parsed_vector {};
    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos)
    {
        parsed_vector.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    parsed_vector.push_back(s.substr(start));
    return parsed_vector;
}

template <typename T>
std::vector<T> split_string(const std::string& s, const std::string& delim, std::function<T(std::string)> func) {
    std::vector<T> parsed_vector;
    auto start = 0U;
    auto end = s.find(delim);
    std::cout << end << "\n";
    while (end != std::string::npos)
    {
        parsed_vector.push_back(func(s.substr(start, end - start)));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    parsed_vector.push_back(func(s.substr(start)));
    return parsed_vector;
}

template <typename T, typename F>
std::vector<T> stringToVector(const std::string& s, F f) {
    std::vector<T> parsed_vector;
    for (const auto& c : s) 
        parsed_vector.push_back(f(c));
    return parsed_vector;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T,S> p) {
    os << "Pair<" << p.first << ", " << p.second << ">";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> v) {
    os << "Vector{";
    for (auto&& it = v.begin(); it != v.end()-1; ++it) os << *it << ", ";
    os << v.back() << "}";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::deque<T> v) {
    os << "Vector{";
    for (auto&& it = v.begin(); it != v.end()-1; ++it) os << *it << ", ";
    os << v.back() << "}";
    return os;
}

namespace hashes {
    template <typename T, typename U>
    struct PairHash {
        size_t operator()(const std::pair<T,U>& p) const {
            return std::hash<T>()(p.first) ^ std::hash<U>()(p.second); 
        }
    };

    template <typename T, typename U>
    struct UserPairHash {
        size_t operator()(const std::pair<T, U> p) const {
            return (p.first)() ^ (p.first)();
        }
    };
};