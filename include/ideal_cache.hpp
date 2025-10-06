#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace IdealCache {

template <typename KeyT = int>
class IdealCache {
public:
    IdealCache(size_t& size, size_t& num_elems, 
               std::vector<KeyT>& input_data);
    
    bool lookup_update(const KeyT& key, const size_t cur_step);
    void make_next_use_map();

private:
    size_t size_;
    size_t num_elems_;
    
    std::vector<KeyT> input_data_;
    
    std::unordered_set<KeyT> cache_;
    std::unordered_map<KeyT, std::vector<size_t>> next_use_map_;
    std::unordered_map<KeyT, size_t> next_use_index_;
    void push_out_unpopular(size_t );
};

template <typename  KeyT>
IdealCache<KeyT>::IdealCache(size_t& size, size_t& num_elems, 
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
    next_use_index_.clear();
    
    for (size_t it = 0; it < num_elems_; ++it) {
        auto key = input_data_[it];
        next_use_map_[key].push_back(it);
    }
    
    for (auto& [key, _] : next_use_map_) {
        next_use_index_[key] = 0;
    }
}

template <typename KeyT>
bool IdealCache<KeyT>::lookup_update(const KeyT& key, const size_t cur_step) {
    if (cache_.find(key) != cache_.end()) {
        return true;
    }
    if (cache_.size() >= size_) {
        IdealCache<KeyT>::push_out_unpopular(cur_step);
    }
    cache_.insert(key);
    return false;
}

template <typename KeyT>
void IdealCache<KeyT>::push_out_unpopular(size_t cur_step) {    
    if (cache_.empty()) { return; }

    KeyT victim_key{};
    size_t latest_usage = 0;

    for(auto& key : cache_) {
        auto next_use_it = next_use_map_.find(key);

        if (next_use_it == next_use_map_.end()) {
            victim_key = key;
            break;
        }
        
        std::vector<size_t>& access_times = next_use_it->second;
        size_t& idx = next_use_index_[key];

        while (idx < access_times.size() && access_times[idx] <= cur_step) {
            ++idx;
        }
        
        if (idx == access_times.size()) {
            victim_key = key;
            break;
        }

        size_t next_usage = access_times[idx];
        if (next_usage > latest_usage) {
            latest_usage = next_usage;
            victim_key = key;
        }
    }
    
    cache_.erase(victim_key);
}
} //namespace IdealCache    
