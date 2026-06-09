#ifndef MAPLE_UNORDERED_MAP_HPP
#define MAPLE_UNORDERED_MAP_HPP

#include "maple/hashtable.hpp"
#include "maple/util.hpp"

namespace maple{

template<typename Key,typename Value,typename Hash=std::hash<Key>,typename KeyEqual=std::equal_to<Key>>
class unordered_map{
public:
    using value_type=pair<const Key,Value>;

private:
    struct MapHash{
        size_t operator()(const value_type& kv)const{
            return Hash()(kv.first);
        }
    };
    struct MapEqual{
        bool operator()(const value_type& a,const value_type& b)const{
            return KeyEqual()(a.first,b.first);
        }
    };
    using HT=hashtable<value_type,MapHash,MapEqual>;

public:
    using iterator=typename HT::iterator;
    
    size_t size()const{ return ht_.size(); }
    void insert(const value_type& kv){ ht_.insert(kv); }
    Value& operator[](const Key& key) {
        value_type dummy(key,Value());
        auto it=ht_.find(dummy);
        if (it==ht_.end()) {
            ht_.insert(dummy);
            it=ht_.find(dummy);
        }
        return it->second;
    }

    iterator find(const Key& key) {
        return ht_.find(value_type(key,Value()));
    }
    iterator begin(){ return ht_.begin(); }
    iterator end(){ return ht_.end(); }

private:
    HT ht_;
};
}//namespace maple

#endif
