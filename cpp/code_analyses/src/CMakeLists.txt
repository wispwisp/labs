cmake_minimum_required(VERSION 3.8)

project(move_research LANGUAGES CXX)


find_library(GTEST_LIBRARY gtest)
find_library(GMOCK_LIBRARY gmock)
find_library(PTHREAD_LIBRARY pthread)


# ************
# * Test debug
add_executable(tests2 tests.cpp)

set_target_properties(tests2 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_definitions(tests2
  PRIVATE _GLIBCXX_DEBUG
  PRIVATE _GLIBCXX_DEBUG_PEDANTIC)

target_link_libraries(tests2
  ${GTEST_LIBRARY}
  ${GMOCK_LIBRARY}
  ${PTHREAD_LIBRARY})


# ****************
# * Test sanitized
add_executable(tests tests.cpp)

target_compile_features(tests PUBLIC cxx_std_17)

set_target_properties(tests PROPERTIES
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON)

target_compile_options(tests
  PRIVATE "-Wall"
  PRIVATE "-Wextra"
  PRIVATE "-Wshadow"
  PRIVATE "-pedantic"
  PRIVATE "-Werror"
  PRIVATE "-Weffc++"
  PRIVATE "-O2")

# Sanitizers
target_compile_options(tests
  PRIVATE "-g"
  PRIVATE "-fno-omit-frame-pointer"
  PRIVATE "-fno-optimize-sibling-calls"
  PRIVATE "-fsanitize=address")
target_link_libraries(tests
  -fsanitize=address
)

target_link_libraries(tests
  ${GTEST_LIBRARY}
  ${GMOCK_LIBRARY}
  ${PTHREAD_LIBRARY})
