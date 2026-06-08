#include <iostream>
#include <cassert>
#include "maple/set.hpp"
#include "maple/map.hpp"

int main() {
    // 测试 set
    {
        maple::set<int> s;
        s.insert(5); s.insert(3); s.insert(7);
        assert(s.size() == 3);

        int expected[] = { 3, 5, 7 };
        int i = 0;
        for (auto it = s.begin(); it != s.end(); ++it) {
            assert(*it == expected[i++]);
        }
        assert(s.find(5) != s.end());
        assert(s.find(10) == s.end());
    }
    std::cout << "[1] set PASSED" << std::endl;

    // 测试 map
    {
        maple::map<int, std::string> m;
        m.insert({ 1, "one" });
        m.insert({ 2, "two" });
        m[3] = "three";

        assert(m.size() == 3);
        assert(m.find(2) != m.end());
        assert(m[3] == "three");
        assert(m[1] == "one");
    }
    std::cout << "[2] map PASSED" << std::endl;

    std::cout << "set & map all pass" << std::endl;
    return 0;
}