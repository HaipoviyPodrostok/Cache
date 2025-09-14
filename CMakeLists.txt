cmake_minimum_required(VERSION 3.11)
project("TwoQcache")

SET(SRCS 
    main.cpp
    source/TwoQCache.cpp
)

add_library(TwoQCache_lib STATIC ${SRCS})
target_include_directories(TwoQCache_lib PUBLIC "include")

add_executable(TwoQCache.x main.cpp)
target_link_libraries(TwoQCache.x TwoQCache_lib)