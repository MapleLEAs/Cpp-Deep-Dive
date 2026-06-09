#ifndef MAPLE_HASHTABLE_HPP
#define MAPLE_HASHTABLE_HPP

#include <vector>
#include <cstddef>
#include "maple/allocator.hpp"
#include "maple/construct.hpp"
#include "maple/iterator.hpp"
#include "maple/util.hpp"

namespace maple{
	// 质数表，桶数量
	static const size_t prime_list[] = {
	    53, 97, 193, 389, 769,
	    1543, 3079, 6151, 12289, 24593,
	    49157, 98317, 196613, 393241, 786433,
	    1572869, 3145739, 6291469, 12582917, 25165843
	};
	
	template <typename T>
	struct hashtable_node {
	    T value;
	    hashtable_node* next;
	    hashtable_node(const T& val) : value(val), next(nullptr) {}
	};
	
	template <typename T>
	struct hashtable_iterator{
		using value_type=T;
	    using pointer=T*;
	    using reference=T&;
	    using difference_type=std::ptrdiff_t;
	    using iterator_category=forward_iterator_tag;
	
	    hashtable_node<T>* node;
	    hashtable_node<T>** bucket;
	    hashtable_node<T>** bucket_end;
	    
	    hashtable_iterator():node(nullptr), bucket(nullptr), bucket_end(nullptr) {}
	    
	    reference operator*()const { return node->value; }
    	pointer operator->()const { return &(node->value); }
    	
    	// 前置 ++
	    hashtable_iterator& operator++() {
	        if (node->next) {
	            node = node->next;
	        } else {
	            ++bucket;
	            while (bucket != bucket_end && *bucket == nullptr) ++bucket;
	            node = (bucket == bucket_end) ? nullptr : *bucket;
	        }
	        return *this;
	    }
	
	    // 后置 ++
	    hashtable_iterator operator++(int) {
	        auto tmp = *this;
	        ++(*this);
	        return tmp;
	    }
	
	    // 相等判断
	    bool operator==(const hashtable_iterator& other) const {
	        return node == other.node;
	    }
	
	    // 不等判断
	    bool operator!=(const hashtable_iterator& other) const {
	        return node != other.node;
	    }
	};
	
	template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
	class hashtable{
		public:
			using iterator=hashtable_iterator<Key>;
			
			hashtable() : bucket_count_(53), size_(0) {
		        buckets_.resize(bucket_count_, nullptr);
		    }
		
		    ~hashtable() { clear(); }
		    
		    size_t size()const{return size_;}
		    
		    void insert(const Key& key) {
		        size_t idx = hash_(key) % bucket_count_;
		        auto* node = new hashtable_node<Key>(key);
		        node->next = buckets_[idx];
		        buckets_[idx] = node;
		        ++size_;
		
		        if (size_ > bucket_count_) rehash();
		    }
		    
		    iterator find(const Key& key) {
		        size_t idx = hash_(key) % bucket_count_;
		        for (auto* p = buckets_[idx]; p; p = p->next) {
		            if (key_equal_(p->value, key)) return make_iter(p, idx);
		        }
		        return end();
		    }
		    
		    void erase(const Key& key) {
		        size_t idx = hash_(key) % bucket_count_;
		        hashtable_node<Key>* prev = nullptr;
		        for (auto* p = buckets_[idx]; p; p = p->next) {
		            if (key_equal_(p->value, key)) {
		                if (prev) prev->next = p->next;
		                else buckets_[idx] = p->next;
		                delete p;
		                --size_;
		                return;
		            }
		            prev = p;
		        }
		    }
		    
		    iterator begin() {
		        for (size_t i = 0; i < bucket_count_; ++i)
		            if (buckets_[i]) return make_iter(buckets_[i], i);
		        return end();
		    }
		
		    iterator end() {
		        iterator it;
		        it.bucket = buckets_.data() + bucket_count_;
		        it.bucket_end = buckets_.data() + bucket_count_;
		        return it;
		    }
		    
		    void clear() {
		        for (size_t i = 0; i < bucket_count_; ++i) {
		            auto* p = buckets_[i];
		            while (p) { auto* next = p->next; delete p; p = next; }
		            buckets_[i] = nullptr;
		        }
		        size_ = 0;
		    }
		private:
		    std::vector<hashtable_node<Key>*> buckets_;
		    size_t bucket_count_;
		    size_t size_;
		    Hash hash_;
		    KeyEqual key_equal_;
		
		    iterator make_iter(hashtable_node<Key>* node, size_t idx) {
		        iterator it;
		        it.node = node;
		        it.bucket = buckets_.data() + idx;
		        it.bucket_end = buckets_.data() + bucket_count_;
		        return it;
		    }
		
		    void rehash() {
		        auto old_buckets = std::move(buckets_);
		        bucket_count_ = next_prime(bucket_count_ * 2);
		        buckets_.resize(bucket_count_, nullptr);
		
		        for (auto& head : old_buckets) {
		            auto* p = head;
		            while (p) {
		                auto* next = p->next;
		                size_t idx = hash_(p->value) % bucket_count_;
		                p->next = buckets_[idx];
		                buckets_[idx] = p;
		                p = next;
		            }
		        }
		    }
		
		    size_t next_prime(size_t n) {
		        for (size_t p : prime_list) if (p >= n) return p;
		        return prime_list[19];
		    }
	};
}//namespace maple

#endif
