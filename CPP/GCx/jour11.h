#include <string>
#include <vector>
#include <deque>
#include <functional>

class Monkey{
    public:
        std::deque<unsigned long> items;
        int function_arg_2;
        std::function<unsigned long(unsigned long, unsigned long)> oper;
        std::function<unsigned long(unsigned long)> function;
        int divisibility_criteria;
        int monkey_true;
        int monkey_false;
        unsigned long monkey_business{0};
    
    public :
        void throw_item(unsigned long worry_level, std::unordered_map<int, Monkey>& monkeys);
        Monkey(std::vector<std::string> vec, int first);
        Monkey();

        void turn(std::unordered_map<int, Monkey>& monkeys);
};