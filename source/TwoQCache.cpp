#include "TwoQCache.hpp"

#include <iostream>
#include <cassert>
#include <list>
#include <unordered_map>
#include <cstddef>

namespace two_q_cache {

template <typename KeyT>
TwoQCache<KeyT>::TwoQCache(size_t size) : size_(size) {
    if (size_ < 3) {
        throw std::invalid_argument("2Q cache size must be >= 3");
    }
    
    in_size_  = std::max(static_cast<size_t>(1), size_ / 4);
    out_size_ = std::max(static_cast<size_t>(1), size_ / 2);
    hot_size_ = size_ - in_size_ - out_size_;
}

template <typename KeyT>
bool TwoQCache<KeyT>::lookup_update(KeyT key) {
    if (hot_hash_.find(key) != hot_hash_.end()) {
        auto elem_it = hot_hash_[key];
        if (elem_it != hot_.begin()) {
            hot_.splice(hot_.begin(), hot_, elem_it);
        }
        hits_++;
        return true;
    }

    if (in_hash_.find(key) != in_hash_.end()) {
        auto elem_it = in_hash_[key];
        if (elem_it != in_.begin()) {
            in_.splice(in_.begin(), in_, elem_it);
        }
        return true;
    }

    if (out_hash_.find(key) != out_hash_.end()) {
        move_to_hot(key);
        return true;
    }

    if (in_.size() < in_size_) {
        in_.push_front(key);
        in_hash_[key] = in_.begin();
    } else {
        if (out_.size() >= out_size_) {
            auto last = out_.back();
            out_hash_.erase(last);
            out_.pop_back();
        }
        auto last_in = in_.back();
        in_hash_.erase(last_in);
        in_.pop_back();

        out_.push_front(last_in);
        out_hash_[last_in] = out_.begin();

        in_.push_front(key);
        in_hash_[key] = in_.begin();
    }
    return false;
}

template <typename KeyT>
void TwoQCache<KeyT>::move_to_hot(KeyT key) {
    auto elem_it_out = out_hash_.find(key);
    if (elem_it_out == out_hash_.end()) return;
    out_.erase(elem_it_out->second);
    out_hash_.erase(key);

    if (hot_.size() >= hot_size_) {
        auto last_it = std::prev(hot_.end());
        hot_hash_.erase(*last_it);
        hot_.pop_back();
    }
    hot_.push_front(key);
    hot_hash_[key] = hot_.begin();
    hits_++;
}

template <typename KeyT>
bool TwoQCache<KeyT>::full() const {
    return (in_.size() + out_.size() + hot_.size()) >= size_;
}

template class TwoQCache<int>;
}