#include <iostream>
#include <cassert>
#include <vector>
#include <list>
#include "maple/algorithm.hpp"

int main() {
    // 测试1：find
    {
        std::vector<int> v = { 1, 2, 3, 4, 5 };
        auto it = maple::find(v.begin(), v.end(), 3);
        assert(it != v.end() && *it == 3);
        assert(maple::find(v.begin(), v.end(), 10) == v.end());
    }
    std::cout << "[1] find PASSED" << std::endl;

    // 测试2：count
    {
        std::vector<int> v = { 1, 2, 2, 3, 2 };
        assert(maple::count(v.begin(), v.end(), 2) == 3);
    }
    std::cout << "[2] count PASSED" << std::endl;

    // 测试3：copy + fill
    {
        std::vector<int> src = { 1, 2, 3 };
        std::vector<int> dst(3);
        maple::copy(src.begin(), src.end(), dst.begin());
        assert(dst[0] == 1 && dst[1] == 2 && dst[2] == 3);

        maple::fill(dst.begin(), dst.end(), 42);
        assert(dst[0] == 42 && dst[1] == 42);
    }
    std::cout << "[3] copy + fill PASSED" << std::endl;

    // 测试4：reverse
    {
        std::vector<int> v = { 1, 2, 3, 4 };
        maple::reverse(v.begin(), v.end());
        assert(v[0] == 4 && v[1] == 3 && v[2] == 2 && v[3] == 1);
    }
    std::cout << "[4] reverse PASSED" << std::endl;

    // 测试5：lower_bound / upper_bound
    {
        std::vector<int> v = { 1, 2, 3, 3, 5 };
        auto lo = maple::lower_bound(v.begin(), v.end(), 3);
        auto hi = maple::upper_bound(v.begin(), v.end(), 3);
        assert(lo - v.begin() == 2);
        assert(hi - v.begin() == 4);
        assert(maple::binary_search(v.begin(), v.end(), 3));
        assert(!maple::binary_search(v.begin(), v.end(), 4));
    }
    std::cout << "[5] lower_bound/upper_bound/binary_search PASSED" << std::endl;

    // 测试6：heap 操作
    {
        std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2, 6 };
        maple::make_heap(v.begin(), v.end());
        // 堆顶应该是最大值
        assert(v[0] == 9);

        v.push_back(10);
        maple::push_heap(v.begin(), v.end());
        assert(v[0] == 10);

        maple::pop_heap(v.begin(), v.end());
        assert(v.back() == 10);
        v.pop_back();

        maple::sort_heap(v.begin(), v.end());
        assert(v[0] == 1 && v.back() == 9);
    }
    std::cout << "[6] heap operations PASSED" << std::endl;

    std::cout << "algorithm all pass" << std::endl;
    return 0;
}