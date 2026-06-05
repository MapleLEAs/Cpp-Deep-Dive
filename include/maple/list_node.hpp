#ifndef MAPLE_LIST_NODE_HPP
#define MAPLE_LIST_NODE_HPP

#include <cstddef>
#include "maple/iterator.hpp"
namespace maple{
	template <typename T>
	struct list_node{
		list_node*prev;
		list_node*next;
		T data;
		
		list_node():prev(nullptr),next(nullptr),data(){
		}
		list_node(const T&val):prev(nullptr),next(nullptr),data(val){
		}
	}; 
	
	// 链表迭代器（双向）
	template <typename T>
	struct list_iterator {
	    using value_type        = T;
	    using pointer           = T*;
	    using reference         = T&;
	    using difference_type   = std::ptrdiff_t;
	    using iterator_category = bidirectional_iterator_tag;
	    list_node<T>* node;

	    list_iterator() : node(nullptr) {}
	    list_iterator(list_node<T>* n) : node(n) {}
	
	    reference operator*()  const { return node->data; }
	    pointer   operator->() const { return &(node->data); }
	    
	    // 前置 ++
	    list_iterator& operator++() {
	        node = node->next;
	        return *this;
	    }
	
	    // 后置 ++
	    list_iterator operator++(int) {
	        list_iterator tmp = *this;
	        node = node->next;
	        return tmp;
	    }
	
	    // 前置 --
	    list_iterator& operator--() {
	        node = node->prev;
	        return *this;
	    }
	
	    // 后置 --
	    list_iterator operator--(int) {
	        list_iterator tmp = *this;
	        node = node->prev;
	        return tmp;
	    }
	
	    bool operator==(const list_iterator& other) const { return node == other.node; }
	    bool operator!=(const list_iterator& other) const { return node != other.node; }
};
}//namespace

#endif
