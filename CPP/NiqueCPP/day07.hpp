#include "common/common.hpp"
#include "common/tree.hpp"

#define SMALL_SIZE 100000
#define FINAL_SPACE 40000000
#define TOTAL_DISK_SPACE 70000000

using file = Node<int>;

struct day07 {
    file root;

    day07();

    unsigned long part_one();
    unsigned long part_two();
};
