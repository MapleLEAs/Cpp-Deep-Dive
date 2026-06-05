#ifndef MAPLE_CONSTRUCT_HPP
#define MAPLE_CONSTRUCT_HPP

#include <new>
#include "maple/type_traits.hpp"
#include "maple/util.hpp"

namespace maple{
	// 在已分配内存上构造对象
	template<typename T,typename... Args>
	void construct(T*p,Args&&... args){
		::new(p)T(forward<Args>(args)...);
	}
	
	
	// destroy 的 tag dispatch
	namespace detail{
		template <typename T>
		void destroy_impl(T*P,true_type){
		}
		
		template <typename T>
		void destroy_impl(T*p,false_type){p->~T();}
	}
	
	
	// 单个销毁
	template <typename T>
	void destroy(T* p) {
	    detail::destroy_impl(p, typename is_trivially_destructible<T>::type());
	}
	
	// 批量销毁
	template <typename ForwardIterator>
	void destroy(ForwardIterator first, ForwardIterator last) {
	    for (; first != last; ++first) {
	        destroy(&(*first));
	    }
	}
}//namespace maple

#endif
