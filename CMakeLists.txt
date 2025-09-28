enable_testing()

cmake_minimum_required(VERSION 3.11)
project("two_q_cache")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(cache_lib INTERFACE)
target_include_directories(cache_lib INTERFACE "include")

add_executable(two_q_cache.x two_q_main.cpp)
target_link_libraries(two_q_cache.x PRIVATE cache_lib)

add_executable(ideal_cache.x ideal_main.cpp)
target_link_libraries(ideal_cache.x PRIVATE cache_lib)

# -- two_q tests --
file(GLOB two_q_testfiles "${CMAKE_SOURCE_DIR}/tests/two_q_tests/*.in")
foreach(two_q_file ${two_q_testfiles})
    get_filename_component(two_q_testname "${two_q_file}" NAME_WE)

    add_test(
        NAME ${two_q_testname}
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${two_q_file} ${CMAKE_CURRENT_BINARY_DIR}/two_q_cache.x"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    set_tests_properties(${testname} PROPERTIES DEPENDS two_q_cache.x)

endforeach()

#-- ideal cache tests --
file(GLOB ideal_testfiles "${CMAKE_SOURCE_DIR}/tests/ideal_cache_tests/*.in")
foreach(ideal_file ${ideal_testfiles})
    get_filename_component(ideal_testname "${ideal_file}" NAME_WE)

    add_test(
        NAME ${ideal_testname}
        COMMAND bash -c "${CMAKE_SOURCE_DIR}/runtest.sh ${ideal_file} ${CMAKE_CURRENT_BINARY_DIR}/ideal_cache.x"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

    set_tests_properties(${testname} PROPERTIES DEPENDS ideal_cache.x)
    
endforeach()