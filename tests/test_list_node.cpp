#include <iostream>
#include <cassert>
#include <string>
#include "maple/list_node.hpp"

int main() {
    maple::list_node<int> node1(42);
    maple::list_node<int> node2;

    node1.next = &node2;
    node2.prev = &node1;

    std::cout << "node1: " << node1.data << std::endl;
    std::cout << "node2 via node1.next: " << node1.next->data << std::endl;
    std::cout << "node1 via node2.prev: " << node2.prev->data << std::endl;

    std::cout << "[1] list_node PASSED" << std::endl;

    // 测试2：迭代器
    maple::list_node<int> n1(1), n2(2), n3(3);
    n1.next = &n2; n2.prev = &n1;
    n2.next = &n3; n3.prev = &n2;

    maple::list_iterator<int> it(&n1);

    assert(*it == 1);
    ++it; assert(*it == 2);
    ++it; assert(*it == 3);
    --it; assert(*it == 2);
    auto it2 = it++;
    assert(*it2 == 2 && *it == 3);
    auto it3 = it--;
    assert(*it3 == 3 && *it == 2);

    std::cout << "[2] list_iterator PASSED" << std::endl;
    return 0;
}