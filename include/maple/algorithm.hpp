#ifndef MAPLE_ALGORITHM_HPP
#define MAPLE_ALGORITHM_HPP

#include "maple/iterator.hpp"
#include "maple/util.hpp"

namespace maple{
	// 不修改序列
	//find:查找第一个等于value的元素
	template <typename InputIterator, typename T>
	InputIterator find(InputIterator first,InputIterator last,const T&value){
		while(first!=last){
			if(*first==value)return first;
			++first;
		}
		return last;
	}
	
	//find_if:查找第一个满足pred的元素
	template<typename InputIterator,typename Predicate>
	InputIterator find_if(InputIterator first,InputIterator last,Predicate pred){
		while(first!=last){
			if(pred(*first))return first;
			++first;
		}
		return last;
	}
	
	//count:计数等于value的元素个数
	template <typename InputIterator, typename T>
	typename iterator_traits<InputIterator>::difference_type
	count(InputIterator first,InputIterator last,const T&value){
		typename iterator_traits<InputIterator>::difference_type n = 0;
	    while (first != last) {
	        if (*first == value) ++n;
	        ++first;
	    }
	    return n;
	}
	
	//equal:判断两个区间是否相等
	template <typename InputIterator1, typename InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
	    while (first1 != last1) {
	        if (*first1 != *first2) return false;
	        ++first1; ++first2;
	    }
	    return true;
	}
	
	// 修改序列
	// copy：拷贝区间
	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
	    while (first != last) {
	        *result = *first;
	        ++first; ++result;
	    }
	    return result;
	}
	
	//fill:用value填充区间
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first,ForwardIterator last,const T& value){
		while(first!=last){
			*first=value;
			++first;
		}
	}
	
	//reverse:反转区间 
	template <typename BidirectionalIterator>
	void reverse(BidirectionalIterator first, BidirectionalIterator last){
		while(first!=last&&first!=--last){
			maple::swap(*first,*last);
			++first;
		}
	}
	
	//二分查找(要求有序)
	//lower_bound:第一个 >= value 的位置
	template <typename ForwardIterator, typename T>
	ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value){
		auto len=maple::distance(first,last);
		while(len>0){
			auto half=len/2;
			auto mid=first;
			maple::advance(mid,half);
			if(*mid<value){
				first=++mid;
				len-=half+1; 
			}else{
				len=half;
			}
		}
		return first;
	}
	
	//upper_bound:第一个>value的位置
	template <typename ForwardIterator, typename T>
	ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value){
		auto len = maple::distance(first, last);
	    while (len > 0) {
	        auto half = len / 2;
	        auto mid = first;
	        maple::advance(mid, half);
	        if (value < *mid) {
	            len = half;
	        } else {
	            first = ++mid;
	            len -= half + 1;
	        }
	    }
	    return first;
	}
	
	//binary_search:是否存在
	template <typename ForwardIterator, typename T>
	bool binary_search(ForwardIterator first, ForwardIterator last, const T& value) {
	    auto it = maple::lower_bound(first, last, value);
	    return it != last && !(value < *it);
	}
	
	//堆操作
	//push_heap:插入元素后调整
	template <typename RandomIterator>
	void push_heap(RandomIterator first, RandomIterator last) {
	    if (last - first < 2) return;
	    auto child = (last - first) - 1;
	    while (child > 0) {
	        auto parent = (child - 1) / 2;
	        if (*(first + child) <= *(first + parent)) break;
	        maple::swap(*(first + child), *(first + parent));
	        child = parent;
	    }
	}
	
	// pop_heap：弹出堆顶后调整
	template <typename RandomIterator>
	void pop_heap(RandomIterator first, RandomIterator last){
		if(last-first<2)return ;
		--last;
		maple::swap(*first,*last);
		auto len=last-first;
		auto parent=0;
		while(true){
			auto child=2*parent+1;
			if(child>=len)break;
			if (child + 1 < len && *(first + child) < *(first + child + 1)) ++child;
	        if (*(first + parent) >= *(first + child)) break;
	        maple::swap(*(first + parent), *(first + child));
	        parent = child;
		} 
	}
	
	//make_heap：建堆
	template <typename RandomIterator>
	void make_heap(RandomIterator first, RandomIterator last) {
	    if (last - first < 2) return;
	    auto len = last - first;
	    for (auto i = len / 2 - 1; i >= 0; --i) {
	        auto parent = i;
	        while (true) {
	            auto child = 2 * parent + 1;
	            if (child >= static_cast<decltype(len)>(len)) break;
	            if (child + 1 < static_cast<decltype(len)>(len) && *(first + child) < *(first + child + 1)) ++child;
	            if (*(first + parent) >= *(first + child)) break;
	            maple::swap(*(first + parent), *(first + child));
	            parent = child;
	        }
	    }
	}
	
	// sort_heap：堆排序
	template <typename RandomIterator>
	void sort_heap(RandomIterator first, RandomIterator last) {
	    while (last - first > 1) {
	        pop_heap(first, last--);
	    }
	}
}//namespace maple

#endif
