#include <iostream>
#include <cassert>
#include <string>
#include "maple/shared_ptr.hpp"

struct Obj {
    static int alive;
    int val;
    Obj(int v) : val(v) { alive++; }
    ~Obj() { alive--; }
};
int Obj::alive = 0;

int main() {
    // 测试1：空构造
    {
        maple::shared_ptr<int> sp;
        assert(sp.get() == nullptr);
        assert(sp.use_count() == 0);
    }
    std::cout << "[1] empty construct PASSED" << std::endl;

    // 测试2：裸指针构造
    {
        maple::shared_ptr<int> sp(new int(42));
        assert(*sp == 42);
        assert(sp.use_count() == 1);
    }
    std::cout << "[2] raw pointer construct PASSED" << std::endl;

    // 测试3：拷贝构造
    {
        maple::shared_ptr<int> sp1(new int(10));
        maple::shared_ptr<int> sp2(sp1);
        assert(sp1.use_count() == 2);
        assert(sp2.use_count() == 2);
        assert(*sp2 == 10);
    }
    std::cout << "[3] copy construct PASSED" << std::endl;

    // 测试4：移动构造
    {
        maple::shared_ptr<int> sp1(new int(5));
        maple::shared_ptr<int> sp2(maple::move(sp1));
        assert(sp1.get() == nullptr);
        assert(sp1.use_count() == 0);
        assert(sp2.use_count() == 1);
        assert(*sp2 == 5);
    }
    std::cout << "[4] move construct PASSED" << std::endl;

    // 测试5：拷贝赋值
    {
        maple::shared_ptr<int> sp1(new int(1));
        maple::shared_ptr<int> sp2(new int(2));
        sp2 = sp1;
        assert(sp1.use_count() == 2);
        assert(sp2.use_count() == 2);
        assert(*sp2 == 1);
    }
    std::cout << "[5] copy assignment PASSED" << std::endl;

    // 测试6：移动赋值
    {
        maple::shared_ptr<int> sp1(new int(100));
        maple::shared_ptr<int> sp2(new int(200));
        sp2 = maple::move(sp1);
        assert(sp1.get() == nullptr);
        assert(sp2.use_count() == 1);
        assert(*sp2 == 100);
    }
    std::cout << "[6] move assignment PASSED" << std::endl;

    // 测试7：reset + unique
    {
        maple::shared_ptr<int> sp(new int(7));
        assert(sp.unique());
        sp.reset();
        assert(sp.get() == nullptr);
        assert(sp.use_count() == 0);
    }
    std::cout << "[7] reset + unique PASSED" << std::endl;

    // 测试8：自动析构
    {
        assert(Obj::alive == 0);
        maple::shared_ptr<Obj> sp(new Obj(1));
        assert(Obj::alive == 1);
        {
            maple::shared_ptr<Obj> sp2(sp);
            assert(Obj::alive == 1);
            assert(sp.use_count() == 2);
        }
        assert(sp.use_count() == 1);
        assert(Obj::alive == 1);
    }
    assert(Obj::alive == 0);
    std::cout << "[8] auto delete PASSED" << std::endl;

    // 测试9：operator->
    {
        maple::shared_ptr<std::string> sp(new std::string("hello"));
        assert(sp->size() == 5);
    }
    std::cout << "[9] operator-> PASSED" << std::endl;

    std::cout << "shared_ptr ALL PASS" << std::endl;
    return 0;
}