cmake_minimum_required(VERSION 3.26)
project(OOPLAB1)

set(CMAKE_CXX_STANDARD 17)

enable_testing()


add_executable(OOPLAB1 test.cpp
                        UnorderedList.cpp
                        HashTable.cpp
                        )
target_link_libraries(OOPLAB1 gtest gmock)