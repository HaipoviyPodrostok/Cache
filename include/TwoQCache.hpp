#pragma once

#include <iostream>
#include <functional>
#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace two_q_cache {

template<typename KeyT = int>
class TwoQCache {
private:
    size_t size_;
    size_t in_size_;
    size_t out_size_;
    size_t hot_size_;

    std::list<KeyT> in_;
    std::list<KeyT> out_;
    std::list<KeyT> hot_;
    
    using ListIt = typename std::list<KeyT>::iterator;
    std::unordered_map<KeyT, ListIt> hot_hash_;
    std::unordered_map<KeyT, ListIt> in_hash_;
    std::unordered_map<KeyT, ListIt> out_hash_;

    size_t hits_   = 0;

    bool full() const;
    void move_to_hot(KeyT key);

public:
    explicit TwoQCache(size_t size);
    bool lookup_update(KeyT key);
    size_t get_hits() const { return hits_; }

    void clear();
};

} //namespace two_q_cache