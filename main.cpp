#include "vector-top-it.h"
#include <iostream>
#include <cstddef>
bool test1() {
    using topit::Vector;
    Vector<int> v;
    return v.isEmpty();
}
int main() {
    using test_t = bool (*)();
    test_t tests[] = {
        test1
    };
    std::cout << std::boolalpha;
    for (size_t i = 0; i < sizeof(tests) / sizeof(test_t); ++i) {
        std::cout << tests[i]() << std::endl;
    }
}

