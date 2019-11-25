cmake_minimum_required(VERSION 3.1)

project(move_research)

# target executable
set(SOURCE_EXE tests.cpp)

# libs (objs)
set(SOURCE_LIB Counter.cpp)

# external libs
find_library(GTEST_LIBRARY gtest)
find_library(GMOCK_LIBRARY gmock)
find_library(PTHREAD_LIBRARY pthread)

# include_directories(include)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -pedantic -Werror -Weffc++ -O2")

add_library(mylibs STATIC ${SOURCE_LIB})
add_executable(tests ${SOURCE_EXE})
target_link_libraries(tests mylibs ${GTEST_LIBRARY} ${GMOCK_LIBRARY} ${PTHREAD_LIBRARY})
