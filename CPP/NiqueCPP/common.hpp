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

#include <cstdint>
#include <string>
#include <string_view>
#include <cstring>
#include <vector>
#include <bitset>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <iterator>

#define fwd(x) static_cast<decltype(x)&&>(x)

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