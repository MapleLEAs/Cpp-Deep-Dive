#ifndef MAPLE_WEAK_PTR_HPP
#define MAPLE_WEAK_PTR_HPP

#include "maple/shared_ptr.hpp"

namespace maple {

template <typename T>
	class weak_ptr {
	public:
	    weak_ptr() : ptr_(nullptr), ref_count_(nullptr) {}
	
	    weak_ptr(const shared_ptr<T>& sp)
	        : ptr_(sp.get()), ref_count_(sp.ref_count_ptr()) {}
	
	    weak_ptr(const weak_ptr& other)
	        : ptr_(other.ptr_), ref_count_(other.ref_count_) {}
	
	    weak_ptr(weak_ptr&& other) noexcept
	        : ptr_(other.ptr_), ref_count_(other.ref_count_) {
	        other.ptr_ = nullptr;
	        other.ref_count_ = nullptr;
	    }
	
	    weak_ptr& operator=(const weak_ptr& other) {
	        if (this != &other) {
	            ptr_ = other.ptr_;
	            ref_count_ = other.ref_count_;
	        }
	        return *this;
	    }
	
	    weak_ptr& operator=(weak_ptr&& other) noexcept {
	        if (this != &other) {
	            ptr_ = other.ptr_;
	            ref_count_ = other.ref_count_;
	            other.ptr_ = nullptr;
	            other.ref_count_ = nullptr;
	        }
	        return *this;
	    }
	
	    shared_ptr<T> lock() const {
	        if (expired()) return shared_ptr<T>();
	        return shared_ptr<T>(*this);
	    }
	
	    bool expired() const {
	        return ref_count_ == nullptr || ref_count_->load() == 0;
	    }
	
	    void reset() {
	        ptr_ = nullptr;
	        ref_count_ = nullptr;
	    }
	
	    friend class shared_ptr<T>;
	
	private:
	    T* ptr_;
	    std::atomic<size_t>* ref_count_;
};

} // namespace maple

#endif
