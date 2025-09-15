enable_testing()

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

file(GLOB testfiles "${CMAKE_SOURCE_DIR}/tests/*.in")

foreach(file ${testfiles})
    get_filename_component(testname "${file}" NAME_WE)

    add_test(
        NAME ${testname}
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${file} ${CMAKE_CURRENT_BINARY_DIR}/TwoQCache.x"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    set_tests_properties(${testname} PROPERTIES DEPENDS TwoQCache.x)
endforeach()