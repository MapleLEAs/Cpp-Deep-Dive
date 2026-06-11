#include <iostream>
#include <cassert>
#include <chrono>
#include <vector>
#include "maple/memory_pool.hpp"

struct Node {
    int a, b, c;
    Node(int x = 0) : a(x), b(x + 1), c(x + 2) {}
};

int main() {
    // 测试1：allocate + deallocate
    {
        maple::memory_pool<Node, 64> pool;
        auto* p1 = pool.allocate();
        auto* p2 = pool.allocate();
        assert(p1 != p2);

        pool.deallocate(p1);
        pool.deallocate(p2);
        // 复用
        auto* p3 = pool.allocate();
        assert(p3 == p2 || p3 == p1);
    }
    std::cout << "[1] allocate/deallocate PASSED" << std::endl;

    // 测试2：construct + destroy
    {
        maple::memory_pool<std::string, 32> pool;
        auto* s = pool.construct("hello world");
        assert(*s == "hello world");
        pool.destroy(s);
    }
    std::cout << "[2] construct/destroy PASSED" << std::endl;

    // 测试3：大量分配
    {
        maple::memory_pool<int, 128> pool;
        std::vector<int*> ptrs;
        for (int i = 0; i < 1000; ++i) {
            ptrs.push_back(pool.allocate());
            *ptrs.back() = i;
        }
        for (int i = 0; i < 1000; ++i) {
            assert(*ptrs[i] == i);
        }
        for (auto p : ptrs) pool.deallocate(p);
    }
    std::cout << "[3] large allocate PASSED" << std::endl;

    // 测试4：性能对比
    {
        const int N = 100000;
        auto t1 = std::chrono::steady_clock::now();
        {
            maple::memory_pool<Node, 4096> pool;
            for (int i = 0; i < N; ++i) {
                auto* p = pool.allocate();
                pool.deallocate(p);
            }
        }
        auto t2 = std::chrono::steady_clock::now();
        std::cout << "[4] pool time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << "ms" << std::endl;
    }
    {
        const int N = 100000;
        auto t1 = std::chrono::steady_clock::now();
        for (int i = 0; i < N; ++i) {
            auto* p = new Node;
            delete p;
        }
        auto t2 = std::chrono::steady_clock::now();
        std::cout << "    new/delete time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
            << "ms" << std::endl;
    }

    std::cout << " memory_pool all pass" << std::endl;
    return 0;
}