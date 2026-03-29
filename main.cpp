#include "vector-top-it.h"
#include <iostream>
#include <cstddef>
#include <string>

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

bool test8()
{
    Vector< int > v;
    v.push_back(42);
    return !v.isEmpty() && v.getSize() == 1 && v.at(0) == 42;
}

bool test9()
{
    Vector< int > v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    return v.getSize() == 3 && v[0] == 1 && v.at(1) == 2 && v[2] == 3;
}

bool test10()
{
    Vector< std::string > v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(std::string("v") + std::to_string(i));
    }

    if (v.getSize() != 100) return false;
    if (v.at(0) != "v0") return false;
    if (v.at(1) != "v1") return false;
    if (v.at(50) != "v50") return false;
    if (v.at(99) != "v99") return false;
    return true;
}

bool test11()
{
    Vector< int > lhs;
    Vector< int > rhs;
    return lhs == rhs;
}

bool test12()
{
    Vector< int > lhs;
    Vector< int > rhs;
    lhs.push_back(1);
    rhs.push_back(1);
    lhs.push_back(2);
    rhs.push_back(2);
    lhs.push_back(3);
    rhs.push_back(3);
    return lhs == rhs;
}

bool test13()
{
    Vector< int > lhs;
    Vector< int > rhs;
    lhs.push_back(1);
    lhs.push_back(2);
    rhs.push_back(1);
    return lhs != rhs;
}

bool test14()
{
    Vector< int > lhs;
    Vector< int > rhs;
    lhs.push_back(1);
    rhs.push_back(1);
    lhs.push_back(2);
    rhs.push_back(3);
    return lhs != rhs;
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
        { test7, "Const Vector.at() must throw std::out_of_range if index is out of range" },
        { test8, "Vector.push_back() on empty vector must add element and increase size" },
        { test9, "Vector.push_back() must append elements preserving order" },
        { test10, "Vector.push_back() must keep existing elements after reallocations" },
        { test11, "operator== must return true for two empty vectors" },
        { test12, "operator== must return true for vectors with equal elements in the same order" },
        { test13, "operator!= must return true for vectors with different sizes" },
        { test14, "operator!= must return true for vectors with same size but different elements" }
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
