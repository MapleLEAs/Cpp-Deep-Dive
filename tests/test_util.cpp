#include<iostream>
#include<cassert>
#include<string>
#include "mystl/util.hpp"

int main() {
	//测试改造
	mystl::pair<int, std::string>p(42, "hellow world");
	assert(p.first == 42);
	assert(p.second == "hellow world");
	std::cout << "[1]pair test passed!" << std::endl;

	//测试拷贝
	mystl::pair<int, std::string>p1(42, "hellow world");
	mystl::pair<int,std::string> p2(p1); // 拷贝构造
	assert(p2.first == 42);
	assert(p2.second == "hellow world");
	std::cout << "[2] copy constructor test passed!" << std::endl;

	//测试 make_pair
	auto p3 = mystl::make_pair(3.14, 100);
	assert(p3.first == 3.14 && p3.second == 100);
	std::cout << "[3] make_pair PASSED" << std::endl;

	// 测试4：比较
	mystl::pair<int, int> a(1, 2), b(1, 3);
	assert(a == a);
	assert(a != b);
	assert(a < b);
	assert(!(a > b));
	assert(a <= b);
	std::cout << "[4] comparison PASSED" << std::endl;

	std::cout << "\n pair All pass" << std::endl;
	return 0;

}
