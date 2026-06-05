#ifndef MAPLE_UNINITIALIZED_HPP
#define MAPLE_UNINITIALIZED_HPP

#include "maple/construct.hpp"

/*
allocator.hpp（要内存 和 还内存）
    ↓
construct.hpp（在已经分配好的原始内存上构造对象和销毁对象）
    ↓
uninitialized.hpp（在一整块未初始化的原始内存上批量构造对象，中途失败会回滚）

*/
namespace maple{
	template <typename InputIterator, typename ForwardIterator>
		ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
		    ForwardIterator cur = result;
		    try {
		        for (; first != last; ++first, ++cur) {
		            maple::construct(&(*cur), *first);
		        }
		    } catch (...) {
		        destroy(result, cur);
		        throw;
		    }
		    return cur;
		}
		
	template <typename ForwardIterator, typename T>
		void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
		    ForwardIterator cur = first;
		    try {
		        for (; cur != last; ++cur) {
		            maple::construct(&(*cur), value);
		        }
		    } catch (...) {
		        destroy(first, cur);
		        throw;
		    }
		}

} // namespace maple

#endif
