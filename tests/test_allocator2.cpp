#include <iostream>
#include <vector>
#include <cassert>
#include "maple/allocator.hpp"
#include "maple/construct.hpp"
#include "maple/uninitialized.hpp"

struct Obj {
    static int alive;
    int val;
    Obj(int v) : val(v) { alive++; }
    ~Obj() { alive--; }
};
int Obj::alive = 0;

int main() {
    // 测试1：allocate + construct + destroy
    {
        maple::allocator<int> alloc;
        int* p = alloc.allocate(3);
        maple::construct(p, 42);
        maple::construct(p + 1, 100);
        assert(p[0] == 42 && p[1] == 100);
        maple::destroy(p);
        maple::destroy(p + 1);
        alloc.deallocate(p, 3);
    }
    std::cout << "[1] allocator + construct PASSED" << std::endl;

    // 测试2：uninitialized_copy
    {
        std::vector<int> src = { 1, 2, 3, 4, 5 };
        maple::allocator<int> alloc;
        int* p = alloc.allocate(5);
        maple::uninitialized_copy(src.begin(), src.end(), p);
        for (int i = 0; i < 5; i++) assert(p[i] == src[i]);
        maple::destroy(p, p + 5);
        alloc.deallocate(p, 5);
    }
    std::cout << "[2] uninitialized_copy PASSED" << std::endl;

    // 测试3：uninitialized_fill
    {
        maple::allocator<int> alloc;
        int* p = alloc.allocate(4);
        maple::uninitialized_fill(p, p + 4, 99);
        for (int i = 0; i < 4; i++) assert(p[i] == 99);
        maple::destroy(p, p + 4);
        alloc.deallocate(p, 4);
    }
    std::cout << "[3] uninitialized_fill PASSED" << std::endl;

    // 测试4：复杂类型构造析构计数
    {
        assert(Obj::alive == 0);
        maple::allocator<Obj> alloc;
        Obj* p = alloc.allocate(3);
        maple::construct(p, 1);
        maple::construct(p + 1, 2);
        maple::construct(p + 2, 3);
        assert(Obj::alive == 3);
        maple::destroy(p, p + 3);
        assert(Obj::alive == 0);
        alloc.deallocate(p, 3);
    }
    std::cout << "[4] object alive count PASSED" << std::endl;

    std::cout << "allocator2 all pass" << std::endl;
    return 0;
}