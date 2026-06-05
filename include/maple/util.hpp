#ifndef MAPLE_UTIL_HPP
#define MAPLE_UTIL_HPP
#include "maple/type_traits.hpp"

namespace maple{
	template<typename T1,typename T2>
	struct pair{
		T1 first;
		T2 second;
		//默认改造
		pair():first(),second(){}
		
		//带参数改造
		pair(const T1&a,const T2&b):first(a),second(b){
		} 
		
		//拷贝改造
		pair(const pair&)=default; 
		
		//移动改造 
		pair(pair&&)=default; 
		
		//拷贝赋值
		pair&operator=(const pair&)=default;
		
		//移动赋值 
		pair&operator=(pair&&)=default; 
		
		//swap
		void swap(pair& other) {
		    using std::swap;
		    swap(first, other.first);
		    swap(second, other.second);
		}
	};
	
	//pair 比较符
	template<typename T1,typename T2>
	bool operator==(const pair<T1,T2>&a,const pair<T1,T2>&b){
		return a.first==b.first&&a.second==b.second;
	} 
	
	template<typename T1,typename T2>
	bool operator!=(const pair<T1,T2>&a,const pair<T1,T2>&b){
		return !(a==b);
	}
	
	template<typename T1,typename T2>
	bool operator<(const pair<T1,T2>&a,const pair<T1,T2>&b){
		return a.first<b.first||(!(b.first<a.first)&&(a.second<b.second));
	}
	
	template<typename T1,typename T2>
	bool operator>(const pair<T1,T2>&a,const pair<T1,T2>&b){
		return a.first>b.first||(!(b.first>a.first)&&(a.second>b.second));
	} 
	
	template<typename T1,typename T2>
	bool operator<=(const pair<T1,T2>&a,const pair<T1,T2>&b){
		return a.first<=b.first||(!(b.first>a.first)&&(a.second<=b.second));
	} 
	
	template<typename T1,typename T2>
	bool operator>=(const pair<T1,T2>&a,const pair<T1,T2>&b){
		return a.first>=b.first||(!(b.first<a.first)&&(a.second>=b.second));
	} 
	
	//make_pair
	template<typename T1,typename T2>
	pair<T1,T2>make_pair(T1 a,T2 b){
		return pair<T1,T2>(a,b);
	}
	
	// move
	template <typename T>
	typename remove_reference<T>::type&& move(T&& arg) {
	    return static_cast<typename remove_reference<T>::type&&>(arg);
	}
	
	
	// forward
	template <typename T>
	T&& forward(typename remove_reference<T>::type& arg) {
	    return static_cast<T&&>(arg);
	}
	
	// swap
	template <typename T>
	void swap(T& a, T& b) {
	    T tmp = maple::move(a);
	    a = maple::move(b);
	    b = maple::move(tmp);
	}
	
}// namespace maple


#endif
