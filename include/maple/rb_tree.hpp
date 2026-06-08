#ifndef MAPLE_RB_TREE_HPP
#define MAPLE_RB_TREE_HPP

#include <cstddef>
#include <functional>
#include "maple/iterator.hpp"

namespace maple{
	//颜色 
	enum class rb_color{
		RED,BLACK
	}; 
	
	//红黑树
	template <typename T>
	struct rb_tree_node{
		T value;
		rb_color color;
		rb_tree_node* left;
		rb_tree_node* right;
		rb_tree_node* parent;
		
		rb_tree_node(const T& val)
			:value(val),color(rb_color::RED),left(nullptr),right(nullptr),parent(nullptr)
			{}
	};
	
	// 红黑树迭代器（双向）
	template<typename T>
	struct rb_tree_iterator{
		using value_type=T;
		using pointer=T*;
		using reference=T&;
		using difference_type=std::ptrdiff_t;
		using iterator_category=bidirectional_iterator_tag;
		
		rb_tree_node<T>*node;
		
		rb_tree_iterator():node(nullptr){
		}
		rb_tree_iterator(rb_tree_node<T>* n):node(n){
		}
		
		reference operator*()const{return node->value;}
		pointer operator->()const{return &(node->value);}
		
		// 前置++：找后继
		rb_tree_iterator& operator++(){
			if(node->right){
				// 右子树不为空 → 后继是右子树的最左节点
	            node = node->right;
	            while (node->left) node = node->left;
			}else{
				// 右子树为空 → 往上找第一个"当前节点是左孩子"的祖先
	            rb_tree_node<T>* parent = node->parent;
	            while (parent && node == parent->right) {
	                node = parent;
	                parent = parent->parent;
	            }
	            node = parent;
			}
			return *this;
		}
		
		rb_tree_iterator operator++(int) {
	        rb_tree_iterator tmp = *this;
	        ++(*this);
	        return tmp;
	    }
		
		// 前置--：找前驱（与++对称）
		rb_tree_iterator& operator--(){
			if (node->left) {
	            node = node->left;
	            while (node->right) node = node->right;
	        } else {
	            rb_tree_node<T>* parent = node->parent;
	            while (parent && node == parent->left) {
	                node = parent;
	                parent = parent->parent;
	            }
	            node = parent;
	        }
	        return *this;
		}
		
		rb_tree_iterator operator--(int) {
	        rb_tree_iterator tmp = *this;
	        --(*this);
	        return tmp;
	    }
	
	    bool operator==(const rb_tree_iterator& other) const { return node == other.node; }
	    bool operator!=(const rb_tree_iterator& other) const { return node != other.node; }
	};
	
	// 红黑树类
	template <typename T, typename Compare = std::less<T>>
	class rb_tree{
		public:
			using iterator=rb_tree_iterator<T>;
			rb_tree():root_(nullptr),size_(0){
			}
			size_t size()const{return size_;}
			
			
			//插入
			void insert(const T& val){
				rb_tree_node<T>*node=new rb_tree_node<T>(val);
				rb_tree_node<T>*parent=nullptr;
				rb_tree_node<T>*cur=root_;
				
				// 1. 普通 BST 插入
				while(cur){
					parent=cur;
					if(compare_(val,cur->value)){
						cur=cur->left;
					}else{
						cur=cur->right;
					}
				}
				
				node->parent = parent;
				if (!parent) {
		            root_ = node;
		        } else if (compare_(val, parent->value)) {
		            parent->left = node;
		        } else {
		            parent->right = node;
		        }
		        
		        // 2. 红黑树修复
		        insert_fix(node);
		        ++size_;
			}
		private:
    		rb_tree_node<T>* root_;
			size_t size_;
			Compare compare_;
			//旋转
    		// 左旋：x 的右孩子 y 变成 x 的父亲
    		void rotate_left(rb_tree_node<T>*x){
    			rb_tree_node<T>*y=x->right;
    			x->right=y->left;
    			if (y->left) y->left->parent = x;
    			
    			y->parent=x->parent;
    			if(!x->parent){
    				root_=y;
				}else if(x==x->parent->left){
					x->parent->left=y;
				}else{
					x->parent->right=y;
				}
				
				y->left=x;
				x->parent=y;
			}
			// 右旋：x 的左孩子 y 变成 x 的父亲
		    void rotate_right(rb_tree_node<T>* x) {
		        rb_tree_node<T>* y = x->left;
		        x->left = y->right;
		        if (y->right) y->right->parent = x;
		
		        y->parent = x->parent;
		        if (!x->parent) {
		            root_ = y;
		        } else if (x == x->parent->left) {
		            x->parent->left = y;
		        } else {
		            x->parent->right = y;
		        }
		
		        y->right = x;
		        x->parent = y;
		    }
			
			//插入修复
			void insert_fix(rb_tree_node<T>* node) {
		        while (node->parent && node->parent->color == rb_color::RED) {
		            rb_tree_node<T>* parent = node->parent;
		            rb_tree_node<T>* grand  = parent->parent;
		
		            if (parent == grand->left) {
		                // 叔叔是右孩子
		                rb_tree_node<T>* uncle = grand->right;
		
		                if (uncle!=nullptr && uncle->color == rb_color::RED) {
		                    // 情况 1：叔叔是红色
		                    parent->color = rb_color::BLACK;
		                    uncle->color  = rb_color::BLACK;
		                    grand->color  = rb_color::RED;
		                    node = grand;  // 往上跳
		                } else {
		                    // 情况 2：叔叔是黑色，当前是右孩子 → 左旋父，变成情况 3
		                    if (node == parent->right) {
		                        node = parent;
		                        rotate_left(node);
		                        parent = node->parent;
		                        grand  = parent->parent;
		                    }
		                    // 情况 3：叔叔是黑色，当前是左孩子 → 右旋爷爷
		                    parent->color = rb_color::BLACK;
		                    grand->color  = rb_color::RED;
		                    rotate_right(grand);
		                }
		            } else {
		                // 对称：叔叔是左孩子
		                rb_tree_node<T>* uncle = grand->left;
		
		                if (uncle && uncle->color == rb_color::RED) {
		                    parent->color = rb_color::BLACK;
		                    uncle->color  = rb_color::BLACK;
		                    grand->color  = rb_color::RED;
		                    node = grand;
		                } else {
		                    if (node == parent->left) {
		                        node = parent;
		                        rotate_right(node);
		                        parent = node->parent;
		                        grand  = parent->parent;
		                    }
		                    parent->color = rb_color::BLACK;
		                    grand->color  = rb_color::RED;
		                    rotate_left(grand);
		                }
		            }
		        }
		        root_->color = rb_color::BLACK;
		    }
		    public:
		        iterator begin() {
			        if (!root_) return iterator(nullptr);
			        rb_tree_node<T>* node = root_;
			        while (node->left) node = node->left;
			        return iterator(node);
			    }
			
			    iterator end() {
			        return iterator(nullptr);
			    }
			
			    iterator find(const T& val) {
			        rb_tree_node<T>* cur = root_;
			        while (cur) {
			            if (compare_(val, cur->value))
			                cur = cur->left;
			            else if (compare_(cur->value, val))
			                cur = cur->right;
			            else
			                return iterator(cur);
			        }
			        return end();
			    }
			
	};
	
}//namespace maple

#endif
