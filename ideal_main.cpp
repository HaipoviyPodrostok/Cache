#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "ideal_cache.hpp"

std::string slow_get_page(int key);

int main() {
    try {
        size_t cache_size = 0;
        size_t num_elems  = 0;

        std::vector<int> input_data;

        if (!(std::cin >> cache_size >> num_elems)) {
            std::cerr << "ERROR: invalid input format" << std::endl;
            return 1;
        }
        
        for (size_t i = 0; i < num_elems; ++i) {
            int key;     
            
            if (!(std::cin >> key)) {
                std::cerr << "ERROR: not enough elements" << std::endl;
                return 1;
            }
            input_data.push_back(key);
        }

        IdealCache::IdealCache<int> ideal_cache(cache_size, num_elems, input_data);

        size_t ideal_hits = 0;
        
        for (size_t i = 0; i < num_elems; ++i) {
            if (ideal_cache.lookup_update(input_data[i], i)) {ideal_hits++;}
        }
        std::cout << ideal_hits << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }    
    catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

std::string slow_get_page(int key) {
    std::string storage_file_name = "assets/pages.txt";
    
    std::ifstream file(storage_file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open: " + storage_file_name);
    }

    std::string line;
    int cur_line = 0;

    while (std::getline(file, line)) {
        if (cur_line == key) {
            return line;
        }
        cur_line++;
    }

    throw std::out_of_range("Key " + std::to_string(key) + " not found in file");
}