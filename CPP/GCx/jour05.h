#include <string>
#include <vector>
#include <stack>
#include <queue>
std::string jour05partie1(std::vector<std::string> lines);

std::vector<std::stack<char>> get_stacks(std::vector<std::string> lines, int delimitation);

std::queue<std::vector<int>> get_instructions(std::vector<std::string> lines, int delimitation);