cmake_minimum_required(VERSION 3.6)
project(PEX1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Contact.cpp ContactList.cpp InsertionSort.cpp MergeSort.cpp QuickSort.cpp)

add_executable(PEX1 ${SOURCE_FILES})
