#include <iostream>
#include <cassert>
#include <string>
#include "maple/unordered_set.hpp"
#include "maple/unordered_map.hpp"

int main() {
    // 测试 unordered_set
    {
        maple::unordered_set<int> us;
        us.insert(5); us.insert(3); us.insert(7);
        assert(us.size() == 3);
        assert(us.find(5) != us.end());
        assert(us.find(10) == us.end());
        us.erase(3);
        assert(us.size() == 2);
    }
    std::cout << "[1] unordered_set PASSED" << std::endl;

    // 测试 unordered_map
    {
        maple::unordered_map<int, std::string> um;
        um.insert({ 1, "one" });
        um.insert({ 2, "two" });
        um[3] = "three";
        assert(um.size() == 3);
        assert(um[2] == "two");
        assert(um[3] == "three");
        assert(um.find(1) != um.end());
        assert(um.find(5) == um.end());
    }
    std::cout << "[2] unordered_map PASSED" << std::endl;

    std::cout << "unordered all pass" << std::endl;
    return 0;
}