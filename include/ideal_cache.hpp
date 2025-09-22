#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

namespace IdealCache {

template <typename KeyT = int>
class IdealCache {
public:
    explicit IdealCache(size_t size, size_t num_elems, 
                        std::vector<KeyT>& input_data);
    
    bool lookup_update(KeyT key);
    void make_next_use_map();

private:
    size_t size_;
    size_t num_elems_;
    
    size_t hits_ = 0;
    
    std::vector<KeyT> input_data_;
    std::vector<KeyT> cache_;
    std::unordered_map<KeyT, std::vector<size_t>> next_use_map_;
    
    void push_out_unpopular();
};

template <typename  KeyT>
IdealCache<KeyT>::IdealCache(size_t size, size_t num_elems, 
                             std::vector<KeyT>& input_data)
    : size_(size), 
      num_elems_(num_elems),  
      input_data_(input_data),
      cache_() {
        cache_.reserve(size_);
        make_next_use_map();
      }

template <typename KeyT>
void IdealCache<KeyT>::make_next_use_map() {
    next_use_map_.clear();
    next_use_map_.reserve(num_elems_);
    for (size_t data_it = 0; data_it < num_elems_; ++data_it) {
        auto key = input_data_[data_it];
        next_use_map_[key].push_back(data_it);
    }
}

template <typename KeyT>
bool IdealCache<KeyT>::lookup_update(KeyT key) {
    if (cache_.find(key) != cache_.end()) {
        return true;
    }
    else {
        if (cache_.size() < size_) {
            cache_.push_back(key);
        }
        else {
            IdealCache<KeyT>::push_out_unpopular();
        }
    }
    return false;
}

template <typename KeyT>
void IdealCache<KeyT>::push_out_unpopular() {
    for (int i = 0; i < size_; ++i) {
        if (next_use_map_.find(cache_[i]) == next_use_map_.end()) {
            cache_.erase(cache_.begin() + i);
        }
        else {
            size_t victim_pos = 0;
            for (int k = 0; k < size_; ++k) {
                auto usage_of_key = (next_use_map_.find(cache_[k]))->second;
                auto latest_usage = usage_of_key.front();
                victim_pos = std::max(victim_pos, latest_usage);
            }
            cache_.erase(input_data_.begin() + victim_pos);
        }
    }
}
} //namespace IdealCache