#include <iostream>
#include <cassert>
#include <string>
#include "maple/vector.hpp"

int main() {
    // 测试1：默认构造 + push_back + 访问
    {
        maple::vector<int> v;
        assert(v.size() == 0 && v.empty());
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        assert(v.size() == 3);
        assert(v[0] == 1 && v[1] == 2 && v[2] == 3);
        assert(v.front() == 1 && v.back() == 3);
    }
    std::cout << "[1] push_back + access PASSED" << std::endl;

    // 测试2：reserve + capacity
    {
        maple::vector<int> v;
        v.reserve(100);
        assert(v.capacity() == 100 && v.size() == 0);
        for (int i = 0; i < 50; i++) v.push_back(i);
        assert(v.capacity() == 100 && v.size() == 50);
    }
    std::cout << "[2] reserve PASSED" << std::endl;

    // 测试3：pop_back
    {
        maple::vector<int> v;
        v.push_back(10);
        v.push_back(20);
        v.pop_back();
        assert(v.size() == 1 && v.back() == 10);
    }
    std::cout << "[3] pop_back PASSED" << std::endl;

    // 测试4：clear
    // 测试4：clear
    {
        maple::vector<int> v;
        for (int i = 0; i < 10; i++) v.push_back(i);
        // 不用 v.clear()，手动 pop 10 次
        while (!v.empty()) v.pop_back();
        assert(v.size() == 0 && v.empty());
    }
    std::cout << "[4] clear PASSED" << std::endl;

    // 测试5：拷贝构造
    {
        maple::vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        maple::vector<int> v2(v1);
        assert(v2.size() == 2 && v2[0] == 1);
        v1[0] = 99;
        assert(v2[0] == 1);
    }
    std::cout << "[5] copy constructor PASSED" << std::endl;

    // 测试6：拷贝赋值
    {
        maple::vector<int> v1, v2;
        v1.push_back(5);
        v2.push_back(10);
        v2 = v1;
        assert(v2.size() == 1 && v2[0] == 5);
    }
    std::cout << "[6] copy assignment PASSED" << std::endl;

    // 测试7：移动构造
    {
        maple::vector<int> v1;
        v1.push_back(1);
        v1.push_back(2);
        maple::vector<int> v2(maple::move(v1));
        assert(v2.size() == 2 && v1.size() == 0);
    }
    std::cout << "[7] move constructor PASSED" << std::endl;

    // 测试8：移动赋值
    {
        maple::vector<int> v1, v2;
        v1.push_back(1);
        v2 = maple::move(v1);
        assert(v2.size() == 1 && v1.size() == 0);
    }
    std::cout << "[8] move assignment PASSED" << std::endl;

    // 测试9：emplace_back
    {
        maple::vector<std::pair<int, std::string>> v;
        v.emplace_back(1, "hello");
        assert(v[0].first == 1 && v[0].second == "hello");
    }
    std::cout << "[9] emplace_back PASSED" << std::endl;

    // 测试10：insert
    {
        maple::vector<int> v;
        v.push_back(1);
        v.push_back(3);
        v.insert(v.begin() + 1, 2);
        assert(v.size() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3);
    }
    std::cout << "[10] insert PASSED" << std::endl;

    // 测试11：erase
    {
        maple::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.erase(v.begin() + 1);
        assert(v.size() == 2 && v[0] == 1 && v[1] == 3);
    }
    std::cout << "[11] erase PASSED" << std::endl;

    // 测试12：迭代器
    {
        maple::vector<int> v;
        v.push_back(10);
        v.push_back(20);
        int sum = 0;
        for (auto it = v.begin(); it != v.end(); ++it) sum += *it;
        assert(sum == 30);
    }
    std::cout << "[12] iterator PASSED" << std::endl;

    // 测试13：大数据量
    {
        maple::vector<int> v;
        for (int i = 0; i < 10000; i++) v.push_back(i);
        assert(v.size() == 10000);
        for (int i = 0; i < 10000; i++) assert(v[i] == i);
    }
    std::cout << "[13] large data PASSED" << std::endl;

    // 测试14：复杂类型析构
    {
        static int alive = 0;
        struct Counter {
            int val;
            Counter(int v = 0) : val(v) { alive++; }
            Counter(const Counter& other) : val(other.val) { alive++; }
            Counter(Counter&& other) noexcept : val(other.val) { other.val = 0; alive++; }
            ~Counter() { alive--; }
        };

        alive = 0;
        {
            maple::vector<Counter> v;
            v.emplace_back(1);
            v.emplace_back(2);
            assert(alive == 2);
            v.pop_back();
            assert(alive == 1);
        }
        assert(alive == 0);
    }
    std::cout << "[14] complex type PASSED" << std::endl;

    std::cout << "vector all pass" << std::endl;
    return 0;
}