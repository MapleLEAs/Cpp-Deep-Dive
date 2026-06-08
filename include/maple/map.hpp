#ifndef MAPLE_MAP_HPP
#define MAPLE_MAP_HPP

#include "maple/rb_tree.hpp"
#include "maple/util.hpp"

namespace maple{
	template <typename Key, typename Value, typename Compare = std::less<Key>>
	class map{
		public:
			using value_type=pair<const Key,Value>;
			
			map()=default;
			
			size_t size()const{
			return tree_.size();}
			
			void insert(const value_type& kv){
				tree_.insert(kv);
			}
			
			Value& operator[](const Key& key) {
		        auto it = find(key);
		        if (it == end()) {
		            insert(pair<const Key, Value>(key, Value()));
		            it = find(key);
		        }
		        return it->second;
		    }
		private:
			struct MapCompare{
				bool operator()(const value_type& a, const value_type& b)const{
					return Compare()(a.first, b.first);
				}
			};
			using Iterator=typename rb_tree<value_type, MapCompare>::iterator;
		public:
			using iterator = Iterator;

		    iterator begin() { return tree_.begin(); }
		    iterator end()   { return tree_.end(); }
		    iterator find(const Key& key) {
		        value_type dummy(key, Value());
		        return tree_.find(dummy);
		    }
		private:
			rb_tree<value_type,MapCompare>tree_;
	};
}//namespace maple

#endif
