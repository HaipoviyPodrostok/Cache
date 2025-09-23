#include <cstddef>
#include <iostream>
#include <vector>

#include "two_q_cache.hpp"
#include "ideal_cache.hpp"

int main() {
    size_t cache_size = 0;
    size_t num_elems  = 0;
    
    std::vector<int> cache;

    if (!(std::cin >> cache_size >> num_elems)) {
        std::cerr << "ERROR: invalid input format" << std::endl;
    }

    if (cache_size < 3) {
        std::cerr << "ERROR: cache size must be >= 3" << std::endl;
    }
    
    for (size_t i = 0; i < num_elems; ++i) {
        int key;     
        
        if (!(std::cin >> key)) {
            std::cerr << "ERROR: not enough elements" << std::endl;
            return 1;
        }
        cache.push_back(key);
    }

    TwoQCache::TwoQCache<int, std::string> two_q_cache(cache_size);

    size_t two_q_hits = 0;

    for (size_t i = 0; i < num_elems; ++i) {
        if (two_q_cache.lookup_update(cache[i])) {two_q_hits++;}
    }

    IdealCache::IdealCache<int> ideal_cache(cache_size, num_elems, cache);

    size_t ideal_hits = 0;
    
    for (size_t i = 0; i < num_elems; ++i) {
        if (ideal_cache.lookup_update(cache[i], i)) {ideal_hits++;}
    }
    std::cout << two_q_hits << std::endl << ideal_hits << std::endl;

    return 0;
}