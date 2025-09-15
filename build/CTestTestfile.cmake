# CMake generated Testfile for 
# Source directory: /home/oleg_pupkov/projects/Cache
# Build directory: /home/oleg_pupkov/projects/Cache/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test1 "bash" "-c" "/home/oleg_pupkov/projects/Cache/runtest.sh /home/oleg_pupkov/projects/Cache/tests/test1.in /home/oleg_pupkov/projects/Cache/build/TwoQCache.x")
set_tests_properties(test1 PROPERTIES  DEPENDS "TwoQCache.x" WORKING_DIRECTORY "/home/oleg_pupkov/projects/Cache/build" _BACKTRACE_TRIPLES "/home/oleg_pupkov/projects/Cache/CMakeLists.txt;22;add_test;/home/oleg_pupkov/projects/Cache/CMakeLists.txt;0;")
add_test(test2 "bash" "-c" "/home/oleg_pupkov/projects/Cache/runtest.sh /home/oleg_pupkov/projects/Cache/tests/test2.in /home/oleg_pupkov/projects/Cache/build/TwoQCache.x")
set_tests_properties(test2 PROPERTIES  DEPENDS "TwoQCache.x" WORKING_DIRECTORY "/home/oleg_pupkov/projects/Cache/build" _BACKTRACE_TRIPLES "/home/oleg_pupkov/projects/Cache/CMakeLists.txt;22;add_test;/home/oleg_pupkov/projects/Cache/CMakeLists.txt;0;")
add_test(test3 "bash" "-c" "/home/oleg_pupkov/projects/Cache/runtest.sh /home/oleg_pupkov/projects/Cache/tests/test3.in /home/oleg_pupkov/projects/Cache/build/TwoQCache.x")
set_tests_properties(test3 PROPERTIES  DEPENDS "TwoQCache.x" WORKING_DIRECTORY "/home/oleg_pupkov/projects/Cache/build" _BACKTRACE_TRIPLES "/home/oleg_pupkov/projects/Cache/CMakeLists.txt;22;add_test;/home/oleg_pupkov/projects/Cache/CMakeLists.txt;0;")
add_test(test4 "bash" "-c" "/home/oleg_pupkov/projects/Cache/runtest.sh /home/oleg_pupkov/projects/Cache/tests/test4.in /home/oleg_pupkov/projects/Cache/build/TwoQCache.x")
set_tests_properties(test4 PROPERTIES  DEPENDS "TwoQCache.x" WORKING_DIRECTORY "/home/oleg_pupkov/projects/Cache/build" _BACKTRACE_TRIPLES "/home/oleg_pupkov/projects/Cache/CMakeLists.txt;22;add_test;/home/oleg_pupkov/projects/Cache/CMakeLists.txt;0;")
add_test(test5 "bash" "-c" "/home/oleg_pupkov/projects/Cache/runtest.sh /home/oleg_pupkov/projects/Cache/tests/test5.in /home/oleg_pupkov/projects/Cache/build/TwoQCache.x")
set_tests_properties(test5 PROPERTIES  DEPENDS "TwoQCache.x" WORKING_DIRECTORY "/home/oleg_pupkov/projects/Cache/build" _BACKTRACE_TRIPLES "/home/oleg_pupkov/projects/Cache/CMakeLists.txt;22;add_test;/home/oleg_pupkov/projects/Cache/CMakeLists.txt;0;")
