#ifndef MAPLE_ALLOCATOR_HPP
#define MAPLE_ALLOCATOR_HPP

#include<new>
#include "maple/util.hpp"

namespace maple{
	template<typename T>
	class allocator{
		public:
			using value_type=T;
			
			allocator()=default;
			
			T*allocate(size_t n){
				return static_cast<T*>(::operator new(n*sizeof(T)));
			}
			void deallocate(T* p,size_t){
				::operator delete(p);
			}	
	};
}//namespace maple

#endif
