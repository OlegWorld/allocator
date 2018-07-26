#include <iostream>
#include <map>
#include "allocator.h"

int factor(int x) {
    if (!x)
        return 1;
    else
        return x * factor(x - 1);
}

int main() {
    std::map<int, int, std::less<>, resize_allocator<std::pair<const int, int>>> m;

    for (int i = 0; i < 10; i++)
        m.emplace(i, factor(i));

    std::cout << "Hello, World!" << std::endl;
    return 0;
}