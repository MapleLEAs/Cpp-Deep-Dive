#ifndef MAPLE_ITERATOR_HPP
#define MAPLE_ITERATOR_HPP

#include "maple/type_traits.hpp"

namespace maple{
	
	
	// 1. 迭代器类型标签（注意继承链）
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : input_iterator_tag {};
	struct bidirectional_iterator_tag : forward_iterator_tag {};
	struct random_access_iterator_tag : bidirectional_iterator_tag {};
	
	
	// 2. iterator_traits
	template <typename Iterator>
	struct iterator_traits{
		using value_type        = typename Iterator::value_type; 
	    using pointer           = typename Iterator::pointer;
	    using reference         = typename Iterator::reference;
	    using difference_type   = typename Iterator::difference_type;
	    using iterator_category = typename Iterator::iterator_category;
	}; 
	
	// T* 指针特化
	template <typename T>
	struct iterator_traits<T*> {
	    using value_type        = T;
	    using pointer           = T*;
	    using reference         = T&;
	    using difference_type   = std::ptrdiff_t;
	    using iterator_category = random_access_iterator_tag;
	};

	// const 指针特化
	template <typename T>
	struct iterator_traits<const T*>{
		using value_type        = T;
	    using pointer           = const T*;
	    using reference         = const T&;
	    using difference_type   = std::ptrdiff_t;
	    using iterator_category = random_access_iterator_tag;
	};
	// 3. advance（标签分派）
	namespace detail{
		// input 版本
		template <typename InputIterator, typename Distance, typename Tag>
		void advance_impl(InputIterator& it, Distance n, Tag) {
		    while (n--) ++it;
		}
		
		// bidirectional 版本
		template <typename BidirectionalIterator, typename Distance>
		void advance_impl(BidirectionalIterator& it, Distance n, bidirectional_iterator_tag) {
		    if (n >= 0) {
		        while (n--) ++it;	
		    } else {
		        while (n++) --it;
		    }
		}

		// random_access 版本
		template <typename RandomIterator, typename Distance>
		void advance_impl(RandomIterator& it, Distance n, random_access_iterator_tag) {
		    it += n;
		}
		
		}//namespace detail
		
		template <typename Iterator, typename Distance>
		void advance(Iterator& it, Distance n) {
		    detail::advance_impl(it, n, typename iterator_traits<Iterator>::iterator_category());
		}
		
		// 4. distance
		namespace detail{
			// input 版本
			template <typename InputIterator, typename Tag>
			typename iterator_traits<InputIterator>::difference_type
			distance_impl(InputIterator first, InputIterator last, Tag) {
			    typename iterator_traits<InputIterator>::difference_type n = 0;
			    while (first != last) {
			        ++first;
			        ++n;
			    }
			    return n;
			}
			
			// random_access 版本
			template <typename RandomIterator>
			typename iterator_traits<RandomIterator>::difference_type
			distance_impl(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
			    return last - first;
			}
		}//namesapce detail
		
		template<typename Iterator>
		typename iterator_traits<Iterator>::difference_type
		distance(Iterator first,Iterator last){
			return detail::distance_impl(first,last,typename iterator_traits<Iterator>::iterator_category());
		}
		
		// 5. next / prev
		template <typename Iterator>
		Iterator next(Iterator it, typename iterator_traits<Iterator>::difference_type n = 1) {
		    advance(it, n);
		    return it;
		}
		
		template <typename Iterator>
		Iterator prev(Iterator it, typename iterator_traits<Iterator>::difference_type n = 1) {
	    	advance(it, -n);
	    	return it;
		}
	}// namespace maple
	
	
#endif
