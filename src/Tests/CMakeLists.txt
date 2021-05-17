add_subdirectory(/usr/src/gtest [binary_dir])
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Tests LinkedListTests.cpp DynamicArrayTests.cpp ArraySequenceTests.cpp ListSequenceTests.cpp SequenceTests.cpp EnumerableTests.cpp ComplexTests.cpp)
target_link_libraries(Tests gtest gtest_main)

