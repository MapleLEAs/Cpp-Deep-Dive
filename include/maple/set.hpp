#ifndef MAPLE_SET_HPP
#define MAPLE_SET_HPP

#include "maple/rb_tree.hpp"

namespace maple{
	template<typename Key,typename Compare=std::less<Key>>
	class set{
		public:
			using iterator=typename rb_tree<Key,Compare>::iterator;
			set()=default;
			size_t size()const{
				return tree_.size();
			}
			void insert(const Key&key){
				tree_.insert(key);
			}
			
			iterator begin(){
				return tree_.begin();
			}
			iterator end(){
				return tree_.end();
			}
			iterator find(const Key&key){
				return tree_.find(key);
			}
		private:
			rb_tree<Key,Compare> tree_;
	};
}//namespace maple

#endif
