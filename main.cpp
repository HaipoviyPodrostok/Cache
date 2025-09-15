#include <iostream>
#include <sstream>

#include "TwoQCache.hpp"

int main() {
    size_t cache_size = 0;
    size_t num_elems  = 0;
    if (!(std::cin >> cache_size >> num_elems)) {
        std::cerr << "ERROR: invalid input format" << std::endl;
    }

    try {
        two_q_cache::TwoQCache<int> cache(cache_size);

        int hits = 0;
        for (size_t i = 0; i < num_elems; ++i) {
            int key;
            if (!(std::cin >> key)) {
                std::cerr << "ERROR: not enough elements" << std::endl;
                return 1;
            }
            if (cache.lookup_update(key)) {
                hits++;
            }
        }

        std::cout << hits << std::endl;
    }
    catch (const std::exception& error) {
        std::cerr << "ERROR: " << error.what() << std::endl;
        return 1;
    }
    return 0;
}