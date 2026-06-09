#ifndef MAPLE_UNORDERED_SET_HPP
#define MAPLE_UNORDERED_SET_HPP

#include "maple/hashtable.hpp"

namespace maple{

template<typename Key,typename Hash=std::hash<Key>,typename KeyEqual=std::equal_to<Key>>
class unordered_set{
public:
    using iterator=typename hashtable<Key, Hash, KeyEqual>::iterator;

    size_t size()const{return ht_.size(); }

    void insert(const Key& key){ ht_.insert(key); }
    void erase(const Key& key){ ht_.erase(key); }

    iterator find(const Key& key){return ht_.find(key); }
    iterator begin(){return ht_.begin(); }
    iterator end(){return ht_.end(); }

private:
    hashtable<Key, Hash, KeyEqual> ht_;
};
}//namespace maple

#endif
