cmake_minimum_required(VERSION 3.19)
project(searcher)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_compile_definitions(TESTS)


set(CMAKE_CXX_STANDARD 20)

add_executable(searcher main.cpp src/ConverterJSON.cpp
                                 include/ConverterJSON.h
                                 src/JSONMissingExeption.cpp
                                 include/JSONMissingExeption.h
                                 src/InvertedIndex.cpp
                                 include/InvertedIndex.h
                                 Tests/tests.cpp
                                 src/SearchServer.cpp
                                 include/SearchServer.h
                                 include/json.hpp)

target_include_directories(searcher PUBLIC include src Tests)

target_link_libraries(searcher PRIVATE gtest_main)
