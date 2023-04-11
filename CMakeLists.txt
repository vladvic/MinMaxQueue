project(MinMaxQueue)
cmake_minimum_required(VERSION 3.0)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_compile_options(-g)
add_executable(test_min_max src/test.cpp src/Profiler.cpp)
target_link_libraries(test_min_max ${GTEST_LIBRARIES})
set_property(TARGET test_min_max PROPERTY CXX_STANDARD 11)

enable_testing()
add_test(AllTestsInFoo test_min_max)
