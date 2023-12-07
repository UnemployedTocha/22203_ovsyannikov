cmake_minimum_required(VERSION 3.26)
project(NewLab1)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(NewLab1
        UnorderedList.cpp
        UnorderedList.h
        HashTable.cpp
        HashTable.h
        test.cpp
)

target_link_libraries(NewLab1 gtest gmock)
