#pragma once

#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <vector>

namespace IdealCache {

template <typename KeyT = int>
class IdealCache {
public:
    IdealCache(size_t size, size_t num_elems, 
                        std::vector<KeyT>& input_data);
    
    bool lookup_update(KeyT key, size_t cur_step);
    void make_next_use_map();

private:
    size_t size_;
    size_t num_elems_;
    
    std::vector<KeyT> input_data_;
    std::vector<KeyT> cache_;
    std::unordered_map<KeyT, std::vector<size_t>> next_use_map_;
    
    void push_out_unpopular(size_t );
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
    
    for (size_t it = 0; it < num_elems_; ++it) {
        auto key = input_data_[it];
        next_use_map_[key].push_back(it);
    }
}

template <typename KeyT>
bool IdealCache<KeyT>::lookup_update(KeyT key, size_t cur_step) {
    if (std::find(cache_.begin(), cache_.end(), key) != cache_.end()) {
        return true;
    }
    else {
        if (cache_.size() >= size_) {
            IdealCache<KeyT>::push_out_unpopular(cur_step);
        }
        cache_.push_back(key);
    }
    return false;
}

template <typename KeyT>
void IdealCache<KeyT>::push_out_unpopular(size_t cur_step) {
    auto victim_it = cache_.begin(); 
    
    if (victim_it == cache_.end()) { return; }
    
    size_t latest_usage = 0;

    for (auto it = cache_.begin(); it != cache_.end(); ++it) {
        auto next_use_it = next_use_map_.find(*it);

        if (next_use_it == next_use_map_.end()) {
            victim_it = it;
            break;
        } else {
            auto& access_times = next_use_it->second;
            while (!access_times.empty() && access_times.front() <= cur_step) {
                access_times.erase(access_times.begin());
            }
            
            if (access_times.empty()) {
                victim_it = it;
                break;
            }
            
            size_t next_usage = next_use_it->second.front();
            
            if (next_usage > latest_usage) {
                latest_usage = next_usage;
                victim_it = it;
            }
        }
    }
    cache_.erase(victim_it);
}
} //namespace IdealCache    
