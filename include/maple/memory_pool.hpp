#ifndef MAPLE_MEMORY_POOL_HPP
#define MAPLE_MEMORY_POOL_HPP

#include <cstddef>
#include "maple/util.hpp"

namespace maple{
	template <typename T, size_t BlockSize = 4096>
	class memory_pool{
		public:
		memory_pool():free_list_(nullptr),blocks_(nullptr){
		}
		
		~memory_pool(){
			// 释放所有分配的内存块
			while(blocks_){
				auto* next=blocks_->next;
	            ::operator delete(blocks_);
	            blocks_ = next;
			}
		}
		
		T*allocate(){
			if(!free_list_){
				allocate_block();
			}
			FreeNode* node = free_list_;
	        free_list_ = node->next;
	        return reinterpret_cast<T*>(node);
		}
		
		void deallocate(T* p){
			p->~T();
			auto* node=reinterpret_cast<FreeNode*>(p);
			node->next=free_list_;
			free_list_=node;
		}
		
		template <typename... Args>
	    T* construct(Args&&... args) {
	        T* p = allocate();
	        ::new(p) T(maple::forward<Args>(args)...);
	        return p;
	    }
	    
	    void destroy(T* p) {
	        deallocate(p);
	    }
	    
	    private:
	    union FreeNode{
	    	T data;
	    	FreeNode* next;
	    	FreeNode():next(nullptr){
			}
			~FreeNode(){
			}
		};
		
		struct MemoryBlock{
			FreeNode nodes[BlockSize];
	        MemoryBlock* next;
	        MemoryBlock() : next(nullptr) {}
		};
		
		FreeNode* free_list_;
    	MemoryBlock* blocks_ = nullptr;
    	
    	void allocate_block() {
	        auto* block = static_cast<MemoryBlock*>(::operator new(sizeof(MemoryBlock)));
	        block->next = blocks_;
	        blocks_ = block;
	
	        // 将新块中所有节点串入空闲链表
	        for (size_t i = 0; i < BlockSize; ++i) {
	            block->nodes[i].next = free_list_;
	            free_list_ = &block->nodes[i];
	        }
	    }
	};
}//namespace

#endif
