project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run detection_test.cpp)
target_link_libraries(Google_Tests_run motor)
target_link_libraries(Google_Tests_run gtest gtest_main)

# linking Google_Tests_run with file which will be tested
