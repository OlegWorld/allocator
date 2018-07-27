#include <iostream>
#include <map>
#include "allocator.h"
#include "simple_list.h"

int factor(int x) {
    if (!x)
        return 1;
    else
        return x * factor(x - 1);
}

using ordinary_map = std::map<int, int>;
using resize_map = std::map<int, int, std::less<>, resize_allocator<std::pair<const int, int>>>;

int main() {
    ordinary_map om;

    for (int i = 0; i < 10; i++)
        om.emplace(i, factor(i));

    resize_map rm;

    for (int i = 0; i < 10; i++)
        rm.emplace(i, factor(i));

    for (const auto& el : rm) {
        std::cout << el.first << " " << el.second << std::endl;
    }

    return 0;
}