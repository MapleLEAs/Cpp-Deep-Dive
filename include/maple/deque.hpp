#ifndef MAPLE_DEQUE_HPP
#define MAPLE_DEQUE_HPP

#include <cstddef>
#include "maple/iterator.hpp"
#include "maple/allocator.hpp"
#include "maple/construct.hpp"

namespace maple{
	template <typename T>
	struct deque_iterator{
		using value_type=T;
		using pointer=T*;
		using reference=T&;
		using difference_type=std::ptrdiff_t;
		using iterator_category=random_access_iterator_tag; 
		
		T*cur;
		T*first;
		T*last;
		T**node;
		
		//默认构造
		deque_iterator() : cur(nullptr), first(nullptr), last(nullptr), node(nullptr) {}
		reference operator*()const{
			return *cur;
		}
		pointer operator->()const{
			return cur;
		}
		
		//前置++
		deque_iterator& operator++(){
			++cur;
			if(cur==last){
				++node;
				first=*node;
				last=first+buffer_size();
				cur=first;
			}
			return *this;
		} 
		// 后置 ++
	    deque_iterator operator++(int) {
	        deque_iterator tmp = *this;
	        ++(*this);
	        return tmp;
	    }
	    
	    // 前置 --
	    deque_iterator& operator--() {
	        if (cur == first) { 
	            --node;         
	            first = *node;
	            last = first + buffer_size();
	            cur = last - 1;
	        } else {
	            --cur;
	        }
	        return *this;
	    }
	
	    // 后置 --
	    deque_iterator operator--(int) {
	        deque_iterator tmp = *this;
	        --(*this);
	        return tmp;
	    }
	    
	    static constexpr size_t buffer_size(){
	    	return sizeof(T)<256?4096/sizeof(T):16;
		}
		bool operator==(const deque_iterator& other)const{return cur==other.cur;}
		bool operator!=(const deque_iterator& other)const{return cur!=other.cur;}
		// operator+=
	    deque_iterator& operator+=(difference_type n) {
	        difference_type offset = n + (cur - first);
	        if (offset >= 0 && offset < static_cast<difference_type>(buffer_size())) {
	            cur += n;
	        } else {
	            difference_type node_offset = offset > 0
	                ? offset / static_cast<difference_type>(buffer_size())
	                : -((-offset - 1) / static_cast<difference_type>(buffer_size())) - 1;
	            node += node_offset;
	            first = *node;
	            last  = first + buffer_size();
	            cur   = first + (offset - node_offset * static_cast<difference_type>(buffer_size()));
	        }
	        return *this;
	    }
	
	    // operator+
	    deque_iterator operator+(difference_type n) const {
	        deque_iterator tmp = *this;
	        return tmp += n;
	    }
	
	    // operator-=
	    deque_iterator& operator-=(difference_type n) {
	        return *this += -n;
	    }
	
	    // operator-
	    deque_iterator operator-(difference_type n) const {
	        deque_iterator tmp = *this;
	        return tmp -= n;
	    }
	
	    // operator- (两个迭代器相减)
	    difference_type operator-(const deque_iterator& other) const {
	        return static_cast<difference_type>(buffer_size()) * (node - other.node)
	               + (cur - first) - (other.cur - other.first);
	    }
	
	    // operator[]
	    reference operator[](difference_type n) const {
	        return *(*this + n);
	    }
	
	    // operator<
	    bool operator<(const deque_iterator& other) const {
	        return node == other.node ? cur < other.cur : node < other.node;
	    }
	};
	
	//deque骨架
	template <typename T>
	class deque {
		public:
			using value_type=T;
			using iterator=deque_iterator<T>;
			using reference=T&;
			using size_type=size_t;
			
			deque()
			:map_(nullptr)
			,map_size_(0)
			,start_()
			,finish_()
			{
				init_map(1);
			}
			
			~deque(){
				if (!empty()) {
			        for (auto it = begin(); it != end(); ++it) {
			            destroy(it.cur);
			        }
			    }
				deallocate_map();
			}
			
			//容量
			size_t size()const{return finish_-start_;}
			bool empty()const{
				return start_==finish_;
			} 
			
			//访问
			reference front(){
				return *start_;
			}
			reference back(){
				return *(finish_-1);
			}
			
			reference operator[](size_t n){
				return start_[n];
			}
			
			//迭代器
			iterator begin(){
				return start_;
			} 
			iterator end(){
				return finish_;
			}
			
			//修改
			void push_back(const T&val){
				if(finish_.cur+1==finish_.last){
					reserve_map_back();
					new_node_at_back();
				}
				construct(finish_.cur,val);
				++finish_;
			}
			
			void push_front(const T& val){
				if(start_.cur==start_.first){
					reserve_map_front();
            		new_node_at_front();
				}
				--start_;
				construct(start_.cur,val);
			}
			
			void pop_back(){
				--finish_;
				destroy(finish_.cur);
			}
			
			void pop_front(){
				destroy(start_.cur);
				++start_;
			}
			
			void clear(){
				for(auto it=begin();it!=end();++it){
					destroy(it.cur);
				}
				start_=iterator();
				finish_=iterator();
			}
		private:
			T**map_;
			size_t map_size_;
			iterator start_;
			iterator finish_;
			allocator<T>data_alloc_;
			allocator<T*>map_alloc_;
			static constexpr size_t buf_sz=deque_iterator<T>::buffer_size();
			
			void init_map(size_t n){
				map_size_=8;
				while(map_size_<n+2)map_size_*=2;
				map_=map_alloc_.allocate(map_size_);
				
				T** nstart=map_+(map_size_-n)/2;
				T** nfinish=nstart+n;
				
				for(T** p=nstart;p<nfinish;++p){
					*p=data_alloc_.allocate(buf_sz);
				} 
				
				start_.node=nstart;
				start_.first=*nstart;
				start_.last=*nstart+buf_sz;
				start_.cur=*nstart;
				
				finish_.node=nfinish-1;
				finish_.first=*(nfinish-1);
				finish_.last=*(nfinish-1)+buf_sz;
				finish_.cur=*(nfinish-1);
			}
			
			// 释放所有缓冲区和中控器
			void deallocate_map(){
				if(map_&& start_.node && finish_.node){
					for(T** p=start_.node;p<=finish_.node;++p){
						data_alloc_.deallocate(*p,buf_sz);
					}
					map_alloc_.deallocate(map_,map_size_);
				}
			}
			
			void reserve_map_back(){
				if(finish_.node+1==map_+map_size_){
					reallocate_map(map_size_*2);
				}
			}
			
			void reserve_map_front() {
		        if (start_.node == map_) {
		            reallocate_map(map_size_ * 2);
		        }
		    }
			void reallocate_map(size_t new_size){
				T** new_map= map_alloc_.allocate(new_size);
		        T** nstart = new_map + (new_size - size()) / 2;
		        T** old_start= start_.node;
		
		        for (T** p = nstart,**q = old_start; q <= finish_.node; ++p, ++q) {
		            *p = *q;
		        }
		
		        map_alloc_.deallocate(map_, map_size_);
		        map_=new_map;
		        map_size_=new_size;
		
		        start_.node=nstart;
		        finish_.node=nstart + (finish_.node - old_start);
			}
			void new_node_at_back(){
				*(finish_.node + 1) = data_alloc_.allocate(buf_sz);
		        ++finish_;
		        finish_.first = *finish_.node;
		        finish_.last  = finish_.first + buf_sz;
		        finish_.cur   = finish_.first;
			}
			void new_node_at_front(){
				*(start_.node - 1) = data_alloc_.allocate(buf_sz);
		        --start_;
		        start_.first = *start_.node;
		        start_.last  = start_.first + buf_sz;
		        start_.cur   = start_.last - 1;
			}
			 
	};
}//namespace

#endif
