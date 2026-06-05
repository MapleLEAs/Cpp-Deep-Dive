#ifndef MAPLE_LIST_HPP
#define MAPLE_LIST_HPP

#include "maple/list_node.hpp"
#include "maple/allocator.hpp"
#include "maple/construct.hpp"
#include "maple/iterator.hpp"
#include "maple/util.hpp"

namespace maple {

template <typename T>
class list {
public:
    using value_type      = T;
    using iterator        = list_iterator<T>;
    using const_iterator  = list_iterator<const T>;
    using reference       = T&;
    using const_reference = const T&;
    using size_type       = size_t;

    // 构造/析构
    list() {
        head_ = alloc_node();
        head_->prev = head_;
        head_->next = head_;
    }

    ~list() {
        clear();
        dealloc_node(head_);
    }

    // 容量
    size_t size()  { return size_; }
    bool   empty() { return size_ == 0; }

    // 访问
    T& front() { return head_->next->data; }
    T& back()  { return head_->prev->data; }

    // 迭代器
    iterator begin() { return iterator(head_->next); }
    iterator end()   { return iterator(head_); }
    

    // 修改
    void push_back(const T& val)  { insert(end(), val); }
    void push_front(const T& val) { insert(begin(), val); }
    void pop_back()  { erase(--end()); }
    void pop_front() { erase(begin()); }

    // insert/erase
    iterator insert(iterator pos, const T& val) {
        list_node<T>* new_node = alloc_node(val);
        list_node<T>* cur = pos.node;

        new_node->next = cur;
        new_node->prev = cur->prev;
        cur->prev->next = new_node;
        cur->prev = new_node;

        ++size_;
        return iterator(new_node);
    }

    iterator erase(iterator pos) {
        list_node<T>* cur = pos.node;
        list_node<T>* ret = cur->next;

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;

        destroy_node(cur);
        --size_;
        return iterator(ret);
    }

    void clear() {
        list_node<T>* cur = head_->next;
        while (cur != head_) {
            list_node<T>* tmp = cur;
            cur = cur->next;
            destroy_node(tmp);
        }
        head_->prev = head_;
        head_->next = head_;
        size_ = 0;
    }

    // 拷贝/移动
    list(const list& other) : list() {
	    for (list_node<T>* cur = other.head_->next; cur != other.head_; cur = cur->next) {
	        push_back(cur->data);
	    }
	}

    list(list&& other) noexcept
        : head_(other.head_)
        , size_(other.size_) {
        other.head_ = alloc_node();
        other.head_->prev = other.head_;
        other.head_->next = other.head_;
        other.size_ = 0;
    }

    list& operator=(const list& other) {
        if (this != &other) {
            clear();
            for (list_node<T>* cur = other.head_->next; cur != other.head_; cur = cur->next) {
		        push_back(cur->data);
		    }
        }
        return *this;
    }

    list& operator=(list&& other) noexcept {
        if (this != &other) {
            clear();
            dealloc_node(head_);

            head_ = other.head_;
            size_ = other.size_;

            other.head_ = alloc_node();
            other.head_->prev = other.head_;
            other.head_->next = other.head_;
            other.size_ = 0;
        }
        return *this;
    }

    void swap(list& other) noexcept {
        maple::swap(head_, other.head_);
        maple::swap(size_, other.size_);
    }

private:
    list_node<T>* head_ = nullptr;
    size_t        size_ = 0;

    list_node<T>* alloc_node(const T& val = T()) {
        list_node<T>* node = static_cast<list_node<T>*>(::operator new(sizeof(list_node<T>)));
        maple::construct(&(node->data), val);
        node->prev = nullptr;
        node->next = nullptr;
        return node;
    }

    void destroy_node(list_node<T>* node) {
        maple::destroy(&(node->data));
        ::operator delete(node);
    }

    void dealloc_node(list_node<T>* node) {
        ::operator delete(node);
    }
};

} // namespace maple

#endif
