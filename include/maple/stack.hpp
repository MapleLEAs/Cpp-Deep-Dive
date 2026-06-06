#ifndef MAPLE_STACK_HPP
#define MAPLE_STACK_HPP

#include "maple/deque.hpp"

namespace maple{
	template <typename T, typename Container = deque<T>>
	class stack {
	public:
	    using value_type=typename Container::value_type;
	    using size_type=typename Container::size_type;
	    using reference=typename Container::reference;
	    using const_reference=typename Container::const_reference;
	
	    stack()=default;
	
	    bool empty() const { return c_.empty(); }
	    size_type size()const { return c_.size(); }
	    reference top(){ return c_.back(); }
	
	    void push(const T& val){ c_.push_back(val); }
	    void pop(){ c_.pop_back(); }
	
	private:
	    Container c_;
	};

} // namespace maple

#endif
