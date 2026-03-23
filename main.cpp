#include "vector-top-it.h"
#include <iostream>
#include <cstddef>

using topit::Vector;

bool test1()
{
    Vector< int > v;
    return v.isEmpty();
}

bool test2()
{
    Vector< int > v;
    return v.getSize() == 0;
}

bool test3()
{
    size_t s = 3ull;
    Vector< int > v(s, 0);
    return v.getSize() == s;
}

bool test4()
{
    constexpr size_t s = 4ull;
    try {
        Vector< int > v(s, 1);
        return v.at(0) == 1;
    } catch (...) {
        return false;
    }
}

bool test5()
{
   constexpr size_t s = 5ull;
    try {
        Vector< int > v(s, 0);
        v.at(s);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

bool test6()
{
    constexpr size_t s = 4ull;
    try {
        const Vector< int > v(s, 9);
        return v.at(0) == 9;
    } catch (...) {
        return false;
    }
}

bool test7()
{
    constexpr size_t s = 5ull;
    try {
        const Vector< int > v(s, 0);
        v.at(s);
        return false;
    } catch (const std::out_of_range&) {
        return true;
    } catch (...) {
        return false;
    }
}

int main() {
    using test_t = bool (*)();
    using case_t = std::pair< test_t, const char* >;
    case_t tests[] = {
        { test1, "Default constructed vector must be empty" },
        { test2, "Default constructed vector size must be zero" },
        { test3, "Vector constructed with size must return correct size" },
        { test4, "Vector.at() must return reference to element if index is in range" },
        { test5, "Vector.at() must throw std::out_of_range if index is out of range" },
        { test6, "Const Vector.at() must return reference to element if index is in range" },
        { test7, "Const Vector.at() must throw std::out_of_range if index is out of range" }
    };

    std::cout << std::boolalpha;
    size_t cnt = sizeof(tests) / sizeof(case_t);
    size_t success_cnt = 0;
    for (size_t i = 0; i < cnt; ++i) {
        bool res = tests[i].first();
        const char * msg = res ? "OK" : "FAILED";
        std::cout << msg << ": " << tests[i].second << "\n";
        if (res) success_cnt++;
    }
    std::cout << "\n";
    std::cout << "Passed " << success_cnt << " out of " << cnt << " tests" << "\n";
    if (cnt == success_cnt) std::cout << "All tests passed" << "\n";
}

