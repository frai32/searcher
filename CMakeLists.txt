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

add_compile_definitions(RELISE)


set(CMAKE_CXX_STANDARD 20)

add_executable(searcher main.cpp src/ConverterJSON.cpp
                                 include/ConverterJSON.h
                                 src/InvertedIndex.cpp
                                 include/InvertedIndex.h
                                 src/SearchServer.cpp
                                 include/SearchServer.h
                                 include/json.hpp
        include/ExeptionClasses/CONFIGMissingExeption.h
        src/ExeptionClasses/CONFIGMissingExeption.cpp
        src/ExeptionClasses/REQUESTSMissingExeption.cpp include/ExeptionClasses/REQUESTSMissingExeption.h)


target_include_directories(searcher PUBLIC include src Tests include/ExeptionClasses src/ExeptionClasses)

target_link_libraries(searcher PRIVATE gtest_main)
