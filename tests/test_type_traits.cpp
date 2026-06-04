#include<iostream>
#include<cassert>
#include"maple/type_traits.hpp"

int main() {
	//测试1: integral_constant
	using two = maple::integral_constant<int, 2>;
	static_assert(two::value == 2);
	std::cout << "[1] integral_constant PASSED" << std::endl;

	//测试2: true_type / false_type
	static_assert(maple::true_type::value == true);
	static_assert(maple::false_type::value == false);
	std::cout << "[2] true_type / false_type PASSED" << std::endl;

	//测试3：remove_reference
	static_assert(maple::is_same<maple::remove_reference<int&>::type, int>::value);
	static_assert(maple::is_same<maple::remove_reference<int&&>::type, int>::value);
	static_assert(maple::is_same<maple::remove_reference<int>::type, int>::value);
	std::cout << "[3] remove_reference PASSED" << std::endl;

	// 测试4：is_same
	static_assert(maple::is_same<int, int>::value);
	static_assert(!maple::is_same<int, double>::value);
	std::cout << "[4] is_same PASSED" << std::endl;

	// 测试5：enable_if
	static_assert(maple::is_same<maple::enable_if<true, int>::type, int>::value);
	std::cout << "[5] enable_if PASSED" << std::endl;

    // 测试6：remove_const
    static_assert(maple::is_same<maple::remove_const<const int>::type, int>::value);
    static_assert(maple::is_same<maple::remove_const<int>::type, int>::value);
    std::cout << "[6] remove_const PASSED" << std::endl;

    // 测试7：is_const
    static_assert(maple::is_const<const int>::value);
    static_assert(!maple::is_const<int>::value);
    std::cout << "[7] is_const PASSED" << std::endl;

    // 测试8：is_integral
    static_assert(maple::is_integral<int>::value);
    static_assert(maple::is_integral<bool>::value);
    static_assert(maple::is_integral<long long>::value);
    static_assert(!maple::is_integral<double>::value);
    std::cout << "[8] is_integral PASSED" << std::endl;

    // 测试9：is_floating_point
    static_assert(maple::is_floating_point<double>::value);
    static_assert(!maple::is_floating_point<int>::value);
    std::cout << "[9] is_floating_point PASSED" << std::endl;

    // 测试10：is_arithmetic
    static_assert(maple::is_arithmetic<int>::value);
    static_assert(maple::is_arithmetic<double>::value);
    static_assert(!maple::is_arithmetic<std::string>::value);
    std::cout << "[10] is_arithmetic PASSED" << std::endl;

    // 测试11：is_pointer
    static_assert(maple::is_pointer<int*>::value);
    static_assert(!maple::is_pointer<int>::value);
    std::cout << "[11] is_pointer PASSED" << std::endl;

    // 测试12：is_reference
    static_assert(maple::is_reference<int&>::value);
    static_assert(maple::is_reference<int&&>::value);
    static_assert(!maple::is_reference<int>::value);
    std::cout << "[12] is_reference PASSED" << std::endl;

    // 测试13：is_array
    static_assert(maple::is_array<int[]>::value);
    static_assert(maple::is_array<int[5]>::value);
    static_assert(!maple::is_array<int>::value);
    std::cout << "[13] is_array PASSED" << std::endl;

    // 测试14：is_void
    static_assert(maple::is_void<void>::value);
    static_assert(maple::is_void<const void>::value);
    static_assert(!maple::is_void<int>::value);
    std::cout << "[14] is_void PASSED" << std::endl;
	std::cout << "[All tests PASSED]" << std::endl;
	return 0;
}