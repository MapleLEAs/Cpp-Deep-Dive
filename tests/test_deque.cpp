#include <iostream>
#include <cassert>
#include "maple/deque.hpp"

int main() {
    std::cout << "start" << std::endl;
    // 测试1
    {
        std::cout << "t1 a" << std::endl;
        maple::deque<int> dq;
        std::cout << "t1 b" << std::endl;
        dq.push_back(1);
        std::cout << "t1 c" << std::endl;
        dq.push_back(2);
        std::cout << "t1 d" << std::endl;
        dq.push_back(3);
        std::cout << "t1 e" << std::endl;
        assert(dq.size() == 3);
        std::cout << "t1 f" << std::endl;
    }
    std::cout << "[1] push_back PASSED" << std::endl;

    // 测试2
    {
        std::cout << "t2 a" << std::endl;
        maple::deque<int> dq;
        std::cout << "t2 b" << std::endl;
        dq.push_front(1);
        std::cout << "t2 c" << std::endl;
        dq.push_front(2);
        std::cout << "t2 d" << std::endl;
    }
    std::cout << "[2] push_front PASSED" << std::endl;

    // 测试3：pop_back / pop_front
    {
        maple::deque<int> dq;
        dq.push_back(1); dq.push_back(2); dq.push_back(3);
        dq.pop_back();
        assert(dq.back() == 2);
        dq.pop_front();
        assert(dq.front() == 2);
    }
    std::cout << "[3] pop_back/pop_front PASSED" << std::endl;

    // 测试4：随机访问
    {
        maple::deque<int> dq;
        for (int i = 0; i < 100; i++) dq.push_back(i);
        assert(dq.size() == 100);
        assert(dq[50] == 50 && dq[99] == 99);
    }
    std::cout << "[4] random access PASSED" << std::endl;

    // 测试5：clear
    {
        maple::deque<int> dq;
        for (int i = 0; i < 50; i++) dq.push_back(i);
        dq.clear();
        assert(dq.empty());
    }
    std::cout << "[5] clear PASSED" << std::endl;

    std::cout << " deque all pass" << std::endl;
    return 0;
}