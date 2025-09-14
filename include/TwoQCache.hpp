#pragma once

#include <iostream>
#include <functional>
#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>

namespace two_q_cache {

template<typename KeyT = int>
class TwoQCache {
private:
    size_t size_;
    size_t in_size_;
    size_t out_size_;
    size_t hot_size_    

    std::list<KeyT> in_;
    std::list<KeyT> out_;
    std::list<KeyT> hot_;
    
    using ListIt = typename std::list<KeyT>::iterator;
    std::unordered_map<int, ListIt> hot_index;
    std::unordered_map<int, ListIt> in_index;
    std::unordered_map<int, ListIt> out_index;

    size_t hits_   = 0;
    size_t misses_ = 0;

    bool full() const;
    void move_to_hot(KeyT key);

public:
    explicit TwoQCache(size_t size);
    bool lookup_update(KeyT key);
    size_t get_hits() const { return hits_; }
};

} //namespace two_q_cache

// namespace twq {
    
// template <class Key, class Value,
//           class KeyHash = std::hash<Key>,
//           class KeyEq   = std::equal_to<Key>>
// class TwoQCache {
// public:
//     using Loader  = std::function<Value(const Key&)>;
//     using EvictCb = std::function<void(const Key&, Value&)>;

//     struct Stats {
//         std::size_t hits = 0;
//         std::size_t misses_cold = 0;
//         std::size_t misses_promote = 0;
//     };

//     TwoQCache()
// }

    
// } //namespace caches

// template <typename T, typename KeyT = int> class cache_t {
//     size_t sz_;
//     std::list<T> cache_;

//     using ListIt = typename std::list<T>::iterator;
//     std::unordered_map<KeyT, ListIt> hash_;

//     cache_t(size_t sz) : sz_(sz) {}

//     bool full() const { return (cache_.size() == sz_); }

//     template <typename F> bool lookup_update(KeyT key, F slow_get_page) {
//         auto hit = hash_.find(key);
//         if (hit == hash.end()) {
//             if (full()) {
//                 hash_.erase(cache_.back());
//                 cache_.pop_back();
//             }
//             cache_.push_front(slow_get_page(key));
//             h
//         }
//     }

    
// }
































