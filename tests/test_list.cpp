#include <iostream>
#include <cassert>
#include "maple/list.hpp"

int main() {
    // 测试1：默认构造 + push_back + 遍历
    {
        maple::list<int> lst;
        assert(lst.empty());
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        assert(lst.size() == 3);
        assert(lst.front() == 1 && lst.back() == 3);

        int expected = 1;
        for (auto it = lst.begin(); it != lst.end(); ++it) {
            assert(*it == expected++);
        }
    }
    std::cout << "[1] push_back PASSED" << std::endl;

    // 测试2：push_front
    {
        maple::list<int> lst;
        lst.push_front(3);
        lst.push_front(2);
        lst.push_front(1);
        assert(lst.front() == 1 && lst.back() == 3);
    }
    std::cout << "[2] push_front PASSED" << std::endl;

    // 测试3：pop_back + pop_front
    {
        maple::list<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.pop_back();
        assert(lst.back() == 2);
        lst.pop_front();
        assert(lst.front() == 2);
    }
    std::cout << "[3] pop_back/pop_front PASSED" << std::endl;

    // 测试4：insert + erase
    {
        maple::list<int> lst;
        lst.push_back(1);
        lst.push_back(3);
        auto it = lst.begin();
        ++it;
        lst.insert(it, 2);
        assert(lst.size() == 3);

        auto it2 = lst.begin();
        assert(*it2++ == 1 && *it2++ == 2 && *it2++ == 3);

        it = lst.begin();
        ++it;
        lst.erase(it);
        assert(lst.size() == 2);
    }
    std::cout << "[4] insert/erase PASSED" << std::endl;

    // 测试5：拷贝
    {
        maple::list<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        maple::list<int> lst2(lst);
        assert(lst2.size() == 2);
        lst.push_back(3);
        assert(lst2.size() == 2);
    }
    std::cout << "[5] copy PASSED" << std::endl;

    // 测试6：移动
    {
        maple::list<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        maple::list<int> lst2(maple::move(lst));
        assert(lst2.size() == 2 && lst.empty());
    }
    std::cout << "[6] move PASSED" << std::endl;

    // 测试7：clear
    {
        maple::list<int> lst;
        for (int i = 0; i < 10; i++) lst.push_back(i);
        lst.clear();
        assert(lst.empty() && lst.size() == 0);
    }
    std::cout << "[7] clear PASSED" << std::endl;

    // 测试8：大数据
    {
        maple::list<int> lst;
        for (int i = 0; i < 10000; i++) lst.push_back(i);
        assert(lst.size() == 10000);
    }
    std::cout << "[8] large data PASSED" << std::endl;

    std::cout << "list all pass" << std::endl;
    return 0;
}