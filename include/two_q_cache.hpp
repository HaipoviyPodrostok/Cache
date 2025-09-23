#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace TwoQCache {

template<typename PageT, typename KeyT = int>
class TwoQCache {
public:
    TwoQCache(size_t size);
    bool lookup_update(KeyT key);

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

    std::unordered_map<KeyT, PageT> page_storage_;

    bool full() const;
    void move_to_hot(KeyT key);
};

template <typename PageT, typename KeyT>
TwoQCache<PageT, KeyT>::TwoQCache(size_t size) : size_(size) {
        
    in_size_  = std::max(static_cast<size_t>(1), size_ / 4);
    out_size_ = std::max(static_cast<size_t>(1), size_ / 2);
    hot_size_ = size_ - in_size_ - out_size_;
}

template <typename PageT, typename KeyT>
bool TwoQCache<PageT, KeyT>::lookup_update(KeyT key) {
    if (hot_hash_.find(key) != hot_hash_.end()) {
        auto elem_it = hot_hash_[key];
        if (elem_it != hot_.begin()) {
            hot_.splice(hot_.begin(), hot_, elem_it);
        }
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

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::move_to_hot(KeyT key) {
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
}

template <typename PageT, typename KeyT>
bool TwoQCache<PageT, KeyT>::full() const {
    return (in_.size() + out_.size() + hot_.size()) >= size_;
}

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::slow_get_page
} //namespace two_q_cache