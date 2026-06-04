#include<iostream>
#include<cassert>
#include<string>
#include "maple/util.hpp"

int main() {
	//测试改造
	maple::pair<int, std::string>p(42, "hellow world");
	assert(p.first == 42);
	assert(p.second == "hellow world");
	std::cout << "[1]pair test passed!" << std::endl;

	//测试拷贝
	maple::pair<int, std::string>p1(42, "hellow world");
	maple::pair<int,std::string> p2(p1); // 拷贝构造
	assert(p2.first == 42);
	assert(p2.second == "hellow world");
	std::cout << "[2] copy constructor test passed!" << std::endl;

	//测试 make_pair
	auto p3 = maple::make_pair(3.14, 100);
	assert(p3.first == 3.14 && p3.second == 100);
	std::cout << "[3] make_pair PASSED" << std::endl;

	// 测试4：比较
	maple::pair<int, int> a(1, 2), b(1, 3);
	assert(a == a);
	assert(a != b);
	assert(a < b);
	assert(!(a > b));
	assert(a <= b);
	std::cout << "[4] comparison PASSED" << std::endl;

	// 测试5：move
	std::string s1 = "hello";
	std::string s2 = maple::move(s1);  // s1 被移动走
	assert(s1.empty());                // 移动后 s1 为空
	assert(s2 == "hello");
	std::cout << "[5] move PASSED" << std::endl;

	// 测试6：forward
	auto forward_test = [](auto&& arg) -> std::string {
		// forward 保持值类别：左值→左值，右值→右值
		return maple::forward<decltype(arg)>(arg);
		};
	std::string s3 = "world";
	assert(forward_test(s3) == "world");           // 传左值
	assert(forward_test(std::string("!")) == "!");  // 传右值
	std::cout << "[6] forward PASSED" << std::endl;

	std::cout << "ALL TEST PASS" << std::endl;
	return 0;

}
