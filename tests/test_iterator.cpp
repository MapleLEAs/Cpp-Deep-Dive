#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include "maple/iterator.hpp"

int main() {
    // 测试1：iterator_traits 对指针
    using traits_ptr = maple::iterator_traits<int*>;
    static_assert(maple::is_same<traits_ptr::value_type, int>::value);
    static_assert(maple::is_same<traits_ptr::iterator_category, maple::random_access_iterator_tag>::value);
    std::cout << "[1] iterator_traits<int*> PASSED" << std::endl;

    // 测试2：iterator_traits 对 const 指针
    using traits_cptr = maple::iterator_traits<const double*>;
    static_assert(maple::is_same<traits_cptr::value_type, double>::value);
    std::cout << "[2] iterator_traits<const T*> PASSED" << std::endl;

    // 测试3：advance 对随机访问
    int arr[] = { 1, 2, 3, 4, 5 };
    int* p = arr;
    maple::advance(p, 3);
    assert(*p == 4);
    std::cout << "[3] advance (random_access) PASSED" << std::endl;

    // 测试4：advance 对输入迭代器
    std::list<int> lst = { 10, 20, 30, 40 };
    auto it = lst.begin();
    maple::advance(it, 2);
    assert(*it == 30);
    std::cout << "[4] advance (input) PASSED" << std::endl;

    // 测试5：distance
    assert(maple::distance(arr, arr + 5) == 5);
    assert(maple::distance(lst.begin(), lst.end()) == 4);
    std::cout << "[5] distance PASSED" << std::endl;

    // 测试6：next / prev
    int* p2 = arr;
    auto p3 = maple::next(p2, 2);
    assert(*p3 == 3);
    auto p4 = maple::prev(p3);
    assert(*p4 == 2);
    std::cout << "[6] next / prev PASSED" << std::endl;

    std::cout << "ALL iterator tests PASSED" << std::endl;
    return 0;
}