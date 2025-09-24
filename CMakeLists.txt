enable_testing()

cmake_minimum_required(VERSION 3.11)
project("two_q_cache")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # to generate compile_commands.json

SET(SRCS 
    main.cpp
    source/two_q_cache.cpp
)

add_library(two_q_cache_lib STATIC ${SRCS})
target_include_directories(two_q_cache_lib PUBLIC "include")

add_executable(two_q_cache.x main.cpp)
target_link_libraries(two_q_cache.x two_q_cache_lib)

file(GLOB testfiles "${CMAKE_SOURCE_DIR}/tests/*.in")

foreach(file ${testfiles})
    get_filename_component(testname "${file}" NAME_WE)

    add_test(
        NAME ${testname}
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${file} ${CMAKE_CURRENT_BINARY_DIR}/two_q_cache.x"
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

    set_tests_properties(${testname} PROPERTIES DEPENDS two_q_cache.x)
endforeach()