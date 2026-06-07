#include <iostream>
#include <cassert>
#include "maple/weak_ptr.hpp"

struct Node {
    maple::shared_ptr<Node> next;
    maple::weak_ptr<Node> prev;
    int val;
    Node(int v) : val(v) {}
    ~Node() { std::cout << "~Node(" << val << ")" << std::endl; }
};

int main() {
    // 测试1：空 weak_ptr
    {
        maple::weak_ptr<int> wp;
        assert(wp.expired());
        assert(wp.lock().get() == nullptr);
    }
    std::cout << "[1] empty weak_ptr PASSED" << std::endl;

    // 测试2：从 shared_ptr 构造 + lock
    {
        maple::shared_ptr<int> sp(new int(42));
        maple::weak_ptr<int> wp(sp);
        assert(!wp.expired());
        auto sp2 = wp.lock();
        assert(*sp2 == 42);
        assert(sp.use_count() == 2);
    }
    std::cout << "[2] lock PASSED" << std::endl;

    // 测试3：expired
    {
        maple::weak_ptr<int> wp;
        {
            maple::shared_ptr<int> sp(new int(10));
            wp = sp;
            assert(!wp.expired());
        }
        assert(wp.expired());
        assert(wp.lock().get() == nullptr);
    }
    std::cout << "[3] expired PASSED" << std::endl;

    // 测试4：打破循环引用
    {
        auto node1 = maple::shared_ptr<Node>(new Node(1));
        auto node2 = maple::shared_ptr<Node>(new Node(2));
        node1->next = node2;
        node2->prev = node1;
        assert(node1.use_count() == 1);
        assert(node2.use_count() == 2);
    }
    std::cout << "[4] cycle broken PASSED" << std::endl;

    std::cout << "weak_ptr all pass" << std::endl;
    return 0;
}