#include <iostream>
#include <cassert>
#include "maple/rb_tree.hpp"

int main() {
    // 测试1：插入 + 大小
    {
        maple::rb_tree<int> tree;
        tree.insert(10);
        tree.insert(5);
        tree.insert(15);
        tree.insert(3);
        tree.insert(7);
        tree.insert(12);
        tree.insert(18);
        assert(tree.size() == 7);
    }
    std::cout << "[1] insert PASSED" << std::endl;

    // 测试2：中序迭代（自动从小到大）
    {
        maple::rb_tree<int> tree;
        tree.insert(5); tree.insert(3); tree.insert(7);
        tree.insert(1); tree.insert(4); tree.insert(6); tree.insert(8);

        int expected[] = { 1, 3, 4, 5, 6, 7, 8 };
        int i = 0;
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            assert(*it == expected[i++]);
        }
        assert(i == 7);
    }
    std::cout << "[2] in-order iteration PASSED" << std::endl;

    // 测试3：查找
    {
        maple::rb_tree<int> tree;
        tree.insert(5); tree.insert(3); tree.insert(7);

        auto it = tree.find(3);
        assert(it != tree.end() && *it == 3);

        it = tree.find(10);
        assert(it == tree.end());
    }
    std::cout << "[3] find PASSED" << std::endl;

    // 测试4：大量插入（验证不崩）
    {
        maple::rb_tree<int> tree;
        for (int i = 0; i < 1000; i++) {
            tree.insert(i);
        }
        assert(tree.size() == 1000);
    }
    std::cout << "[4] large insert PASSED" << std::endl;

    std::cout << "rb_tree all pass" << std::endl;
    return 0;
}