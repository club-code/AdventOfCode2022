#include <string>
#include <vector>
#include <deque>
#include <functional>

class Monkey{
    public:
        std::deque<int> items;
        int function_arg_2;
        std::function<int(int, int)> oper;
        std::function<int(int)> function;
        int divisibility_criteria;
        int monkey_true;
        int monkey_false;
        int monkey_business{0};
    
    public :
        void throw_item(int worry_level, std::unordered_map<int, Monkey>& monkeys);
        Monkey(std::vector<std::string> vec, int first);
        Monkey();

        void turn(std::unordered_map<int, Monkey>& monkeys);
};