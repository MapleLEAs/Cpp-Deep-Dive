#ifndef MAPLE_QUEUE_HPP
#define MAPLE_QUEUE_HPP

#include "maple/deque.hpp"

namespace maple {
	template <typename T, typename Container = deque<T>>
	class queue {
	public:
	    using value_type=typename Container::value_type;
	    using size_type=typename Container::size_type;
	    using reference=typename Container::reference;
	    using const_reference=typename Container::const_reference;
	
	    queue()=default;
	
	    bool empty() const{ return c_.empty(); }
	    size_type size()const { return c_.size(); }
	    reference front(){ return c_.front(); }
	    reference back(){ return c_.back(); }
	
	    void push(const T& val) { c_.push_back(val); }
	    void pop(){ c_.pop_front(); }
	
	private:
	    Container c_;
};

} // namespace maple

#endif
