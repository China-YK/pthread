cmake_minimum_required(VERSION 4.0)
project(thread_learning)

set(CMAKE_CXX_STANDARD 17)

add_executable(thread_learning
        src/CreatThread.cpp)
#add_executable(<target_name> <source1> <source2> ...)

add_executable(testlifepriod
        src/testlifepriod.cpp)


target_link_libraries(thread_learning pthread)

