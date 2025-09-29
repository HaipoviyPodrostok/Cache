#pragma once

#include <functional>
#include <iterator>
#include <list>
#include <unordered_map>

constexpr size_t min_in_size  = 1;
constexpr size_t min_hot_size = 1;

namespace TwoQCache {

template<typename PageT, typename KeyT = int>
class TwoQCache {
public:
    TwoQCache(size_t size, std::function<PageT(KeyT)> slow_get_page);
    bool lookup_update(KeyT key);

private:
    size_t size_;
    size_t in_size_;
    size_t out_size_;
    size_t hot_size_;

    std::list<std::pair<KeyT, PageT>> in_;
    std::list<std::pair<KeyT, PageT>> hot_;
    std::list<KeyT> out_;
    
    using ListIt     = typename std::list<std::pair<KeyT, PageT>>::iterator;
    using OutListIt  = typename std::list<KeyT>::iterator;
    
    using MapIt    = typename std::unordered_map<KeyT, ListIt>::const_iterator;
    using OutMapIt = typename std::unordered_map<KeyT, OutListIt>::iterator;

    std::unordered_map<KeyT, ListIt> hot_hash_;
    std::unordered_map<KeyT, ListIt> in_hash_;
    std::unordered_map<KeyT, OutListIt> out_hash_;

    std::function<PageT(KeyT)> slow_get_page_;

    void move_page_to_begin(std::list<std::pair<KeyT, PageT>>& cache_list,
                            const std::unordered_map<KeyT,ListIt>&, KeyT key);
    void move_out_to_hot(KeyT key);
    void move_in_to_hot (KeyT key);
    void push_to_in_(KeyT key);
    bool full() const;

};

template <typename PageT, typename KeyT>
TwoQCache<PageT, KeyT>::TwoQCache(size_t size,
                                  std::function<PageT(KeyT)> slow_get_page) 
    : size_(size),
      slow_get_page_(slow_get_page) {
        if (size < 3) {
            in_size_  = min_in_size;
            hot_size_ = min_hot_size;
            out_size_ = 0;
        } else {
            in_size_  = std::max(min_in_size,  size_ / 4);
            out_size_ = std::max(min_hot_size, size_ / 2);
            hot_size_ = size_ - in_size_ - out_size_;
        }
}

template <typename PageT, typename KeyT>
bool TwoQCache<PageT, KeyT>::lookup_update(KeyT key) {
    if (hot_hash_.find(key) != hot_hash_.end()) {
        move_page_to_begin(hot_,hot_hash_, key);
        return true;
    }

    if (in_hash_.find(key) != in_hash_.end()) {
        if (out_size_ != 0) {
            move_page_to_begin(in_, in_hash_, key);
        } else {
            move_in_to_hot(key);
        }
        return true;
    }

    if (out_size_ != 0) {
        if (out_hash_.find(key) != out_hash_.end()) {
            move_out_to_hot(key);
            return true;
        }
    }
    
    push_to_in_(key);

    return false;
}

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::move_page_to_begin(std::list<std::pair<KeyT, PageT>>& cache_list, 
                                                const std::unordered_map<KeyT, ListIt>& cache_map,
                                                KeyT key) {
    MapIt elem_it = cache_map.find(key);
    
    if (elem_it->second != cache_list.begin()) {
        cache_list.splice(cache_list.begin(), cache_list, elem_it->second);
    }
}

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::move_out_to_hot(KeyT key) {
    OutMapIt moving_page_map_it = out_hash_.find(key);
    if (moving_page_map_it == out_hash_.end()) {
        return;
    }
    
    OutListIt moving_page_list_it = moving_page_map_it->second;
    PageT moving_page = slow_get_page_(key);

    std::pair<KeyT, PageT> moving_pair_key_page = {key, moving_page};
    
    out_.erase(moving_page_list_it);
    out_hash_.erase(key);

    if (hot_.size() >= hot_size_) {
        ListIt last_it = std::prev(hot_.end());
        hot_hash_.erase(last_it->first);
        hot_.pop_back();
    }
    hot_.push_front(moving_pair_key_page);
    hot_hash_[key] = hot_.begin();
}

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::move_in_to_hot(KeyT key) {
    MapIt moving_page_map_it = in_hash_.find(key);
    if (moving_page_map_it == in_hash_.end()) {
        return;
    }

    std::pair<KeyT, PageT> in_last = in_.back();
    
    ListIt hot_last_it = std::prev(hot_.end());
    KeyT hot_last_key  = hot_last_it->first;
    hot_.pop_back();

    hot_.push_front(in_last);
    hot_hash_[key] = hot_.begin();

    in_hash_.erase(in_last.first);
    in_.pop_back();
}

template <typename PageT, typename KeyT>
bool TwoQCache<PageT, KeyT>::full() const {
    return (in_.size() + out_.size() + hot_.size()) >= size_;
}

template <typename PageT, typename KeyT>
void TwoQCache<PageT, KeyT>::push_to_in_(KeyT key) {
    PageT page = slow_get_page_(key);

    if (in_.size() < in_size_) {
        in_.push_front({key, page});
        in_hash_[key] = in_.begin();
        return;
    }
    
    if (out_.size() >= out_size_ && out_size_ != 0) {
        OutListIt out_last_it = std::prev(out_.end());
        KeyT out_last_key  = *out_last_it;
        out_hash_.erase(out_last_key);
        out_.pop_back();
    }

    std::pair<KeyT, PageT> in_last = in_.back();
    
    in_hash_.erase(in_last.first);
    in_.pop_back();

    if (out_size_ != 0) {
        out_.push_front(in_last.first);
        out_hash_[in_last.first] = out_.begin();
    }

    in_.emplace_front(key, page);
    in_hash_[key] = in_.begin();
}
} //namespace TwoQCache