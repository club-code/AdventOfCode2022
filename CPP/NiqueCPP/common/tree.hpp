#include "common.hpp"

#ifndef TREE
#define TREE
#endif 

template <typename T>
struct Node {
    std::vector<Node<T>*> children;
    std::optional<T> val;
    Node<T>* parent;
    std::optional<std::string> name;
    Node() : parent(this) {};
    Node(std::string name) : parent(this), name(name) {}
    Node(Node<T>* parent, std::string name) : parent(parent), name(name) {}
    Node(T val) : val(val), parent(this) {}
    Node(T val, Node<T>* parent) : val(val), parent(parent) {}
    Node(T val, std::string name) : val(val), parent(this), name(name) {};
    Node(T val, Node<T>* parent, std::string name) : val(val), parent(parent), name(name) {};
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
    if (node.name) os << node.name.value();
    os << "{";
    for (const auto child : node.children) os << *child << " | ";
    if (node.val) os << "val : " << node.val.value();
    os << "}";
    return os;
}