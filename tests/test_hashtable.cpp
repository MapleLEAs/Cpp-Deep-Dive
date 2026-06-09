#include <iostream>
#include <cassert>
#include <string>
#include "maple/hashtable.hpp"

int main() {
    // 测试1：插入 + 查找
    {
        maple::hashtable<int> ht;
        ht.insert(1); ht.insert(2); ht.insert(3);
        assert(ht.size() == 3);
        assert(ht.find(2) != ht.end());
        assert(ht.find(5) == ht.end());
    }
    std::cout << "[1] insert + find PASSED" << std::endl;

    // 测试2：删除
    {
        maple::hashtable<int> ht;
        ht.insert(10); ht.insert(20); ht.insert(30);
        ht.erase(20);
        assert(ht.size() == 2);
        assert(ht.find(20) == ht.end());
        assert(ht.find(10) != ht.end());
    }
    std::cout << "[2] erase PASSED" << std::endl;

    // 测试3：迭代
    {
        maple::hashtable<int> ht;
        ht.insert(5); ht.insert(15); ht.insert(25);
        int count = 0;
        for (auto it = ht.begin(); it != ht.end(); ++it) count++;
        assert(count == 3);
    }
    std::cout << "[3] iteration PASSED" << std::endl;

    // 测试4：大量插入 + rehash
    {
        maple::hashtable<int> ht;
        for (int i = 0; i < 1000; i++) ht.insert(i);
        assert(ht.size() == 1000);
        for (int i = 0; i < 1000; i++) assert(ht.find(i) != ht.end());
    }
    std::cout << "[4] rehash + large insert PASSED" << std::endl;

    // 测试5：string key
    {
        maple::hashtable<std::string> ht;
        ht.insert("hello");
        ht.insert("world");
        assert(ht.find("hello") != ht.end());
        assert(ht.find("xxx") == ht.end());
    }
    std::cout << "[5] string key PASSED" << std::endl;

    std::cout << " hashtable all pass" << std::endl;
    return 0;
}