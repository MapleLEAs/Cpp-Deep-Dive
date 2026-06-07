#ifndef MAPLE_SHARED_PTR_HPP
#define MAPLE_SHARED_PTR_HPP

#include <cstddef>
#include <atomic>
#include "maple/util.hpp"

namespace maple{
	template<typename T>
	class shared_ptr{
	public: 
		//构造
		shared_ptr():ptr_(nullptr),ref_count_(nullptr){
			
		}
		
		// 裸指针构造
    	explicit shared_ptr(T* p) : ptr_(p), ref_count_(new std::atomic<size_t>(1)) {}
		
		//拷贝构造
		shared_ptr(const shared_ptr& other)
			: ptr_(other.ptr_), ref_count_(other.ref_count_) {
        	if (ref_count_) ref_count_->fetch_add(1);
		}
		
		//移动构造
		 shared_ptr( shared_ptr&& other)noexcept
		 :ptr_(other.ptr_)
		 ,ref_count_(other.ref_count_){
		 	other.ptr_=nullptr;
		 	other.ref_count_=nullptr;
		 }
		
		//析构
		~shared_ptr(){
			release();
		} 
		
		//拷贝赋值
		shared_ptr& operator=(const shared_ptr& other){
			if(this!=&other){
				release();
				ptr_=other.ptr_;
				ref_count_=other.ref_count_;
				if(ref_count_)ref_count_->fetch_add(1);
			}
			return *this;
		} 
		
		//移动赋值
		shared_ptr& operator=(shared_ptr&& other)noexcept{
			if(this!=&other){
				release();
				ptr_ = other.ptr_;
            	ref_count_ = other.ref_count_;
            	other.ptr_ = nullptr;
            	other.ref_count_ = nullptr;
			}
			return *this;
		}
		
		// 解引用
	    T& operator*()const { return *ptr_; }
	    T* operator->()const { return ptr_; }
	    T* get()const { return ptr_; }
	    
	    size_t use_count()const{
			return ref_count_ ? ref_count_->load() : 0;
		}
		
		// 是否独占
    	bool unique() const { return use_count() == 1; }

	    // 显式释放
	    void reset() { release(); }
	    
	    bool operator==(const shared_ptr& other) const { return ptr_ == other.ptr_; }
    	bool operator!=(const shared_ptr& other) const { return ptr_ != other.ptr_; }
			
	private:
	    T* ptr_;
	    std::atomic<size_t>* ref_count_;
	
	    void release() {
	        if (ref_count_) {
	            if (ref_count_->fetch_sub(1) == 1) {
	                delete ptr_;
	                delete ref_count_;
	            }
	            ptr_ = nullptr;
	            ref_count_ = nullptr;
	        }
	    }
	}; 
}//namespace maple

#endif
