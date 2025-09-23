#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace TwoQCache {

template<typename PageT, typename KeyT = int>
class TwoQCache {
public:
    TwoQCache(size_t size, const std::string& storage_file_name);
    bool lookup_update(KeyT key);

private:
    size_t size_;
    size_t in_size_;
    size_t out_size_;
    size_t hot_size_;

    std::list<PageT> in_;
    std::list<PageT> out_;
    std::list<PageT> hot_;
    
    using ListIt     = typename std::list<KeyT>::iterator;
    using CacheMapIt = typename std::unordered_map<KeyT, ListIt>::iterator;
    
    std::unordered_map<KeyT, ListIt> hot_hash_;
    std::unordered_map<KeyT, ListIt> in_hash_;
    std::unordered_map<KeyT, ListIt> out_hash_;

    std::string storage_file_name_;

    bool full() const;
    void move_page_to_begin(std::list<PageT>& сache_list, KeyT key);
    void move_to_hot(KeyT key);
    void push_to_in_(KeyT key);
};

template <typename PageT, typename KeyT>
TwoQCache<PageT, KeyT>::TwoQCache(size_t size, const std::string& storage_file_name)
    : size_(size),
      storage_file_name_(storage_file_name) {
        
        in_size_  = std::max(static_cast<size_t>(1), size_ / 4);
        out_size_ = std::max(static_cast<size_t>(1), size_ / 2);
        hot_size_ = size_ - in_size_ - out_size_;
}

template <typename PageT, typename KeyT>
bool TwoQCache<PageT, KeyT>::lookup_update(KeyT key) {
    if (hot_hash_.find(key) != hot_hash_.end()) {
        move_page_to_begin(hot_, key);
        return true;
    }

    if (in_hash_.find(key) != in_hash_.end()) {
        move_page_to_begin(in_, key);
        return true;
    }

    if (out_hash_.find(key) != out_hash_.end()) {
        move_to_hot(key);
        return true;
    }

    else if (in_.size() < in_size_) {
        in_.push_front(key);
        in_hash_[key] = in_.begin();
    } 
    
    else {
        push_to_in_(key);
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
void TwoQCache<PageT, KeyT>::move_page_to_begin(std::list<PageT>& сache_list, KeyT key) {
    CacheMapIt elem_it = hot_hash_[key];
    if (elem_it != сache_list.begin()) {
        сache_list.splice(сache_list.begin(), сache_list, elem_it);
    }
}

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::push_to_in_(KeyT key) {
    if (out_.size() >= out_size_) {
        PageT last = out_.back();
        out_hash_.erase(last);
        out_.pop_back();
    }

    PageT last_in = in_.back();
    in_hash_.erase(last_in);
    in_.pop_back();

    out_.push_front(last_in);
    out_hash_[last_in] = out_.begin();

    in_.push_front(key);
    in_hash_[key] = in_.begin();
}
} //namespace two_q_cache