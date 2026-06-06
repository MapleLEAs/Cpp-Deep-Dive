#include <iostream>
#include <cassert>
#include "maple/stack.hpp"
#include "maple/queue.hpp"

int main() {
    // 测试 stack
    {
        maple::stack<int> st;
        st.push(1); st.push(2); st.push(3);
        assert(st.top() == 3); st.pop();
        assert(st.top() == 2); st.pop();
        assert(st.top() == 1); st.pop();
        assert(st.empty());
    }
    std::cout << "[1] stack PASSED" << std::endl;

    // 测试 queue
    {
        maple::queue<int> q;
        q.push(1); q.push(2); q.push(3);
        assert(q.front() == 1); q.pop();
        assert(q.front() == 2); q.pop();
        assert(q.front() == 3); q.pop();
        assert(q.empty());
    }
    std::cout << "[2] queue PASSED" << std::endl;

    std::cout << " stack & queue all pass" << std::endl;
    return 0;
}