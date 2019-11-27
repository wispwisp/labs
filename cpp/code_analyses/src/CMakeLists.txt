cmake_minimum_required(VERSION 3.1)

project(move_research)


# target executable
set(SOURCE_EXE tests.cpp)


# external libs
find_library(GTEST_LIBRARY gtest)
find_library(GMOCK_LIBRARY gmock)
find_library(PTHREAD_LIBRARY pthread)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -pedantic -Werror -Weffc++ -O2")


# Check by compiller debug
add_definitions(-D_GLIBCXX_DEBUG)
add_definitions(-D_GLIBCXX_DEBUG_PEDANTIC)

# Check by sanitizers
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -fno-omit-frame-pointer -fno-optimize-sibling-calls")


add_executable(tests ${SOURCE_EXE})
target_link_libraries(tests ${GTEST_LIBRARY} ${GMOCK_LIBRARY} ${PTHREAD_LIBRARY})
