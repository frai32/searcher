cmake_minimum_required(VERSION 3.19)
project(searcher)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)


FetchContent_MakeAvailable(googletest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(RELISE)

set(SRC_FILE src/ConverterJSON.cpp
             src/InvertedIndex.cpp
             src/SearchServer.cpp
             src/ExeptionClasses/CONFIGMissingExeption.cpp
             src/ExeptionClasses/REQUESTSMissingExeption.cpp)

set(HEDER_FILES include/ConverterJSON.h
                include/InvertedIndex.h
                include/SearchServer.h
                include/json.hpp
                include/ExeptionClasses/CONFIGMissingExeption.h
                include/ExeptionClasses/REQUESTSMissingExeption.h)



add_executable(searcher main.cpp ${SRC_FILE} ${HEDER_FILES})

add_executable(searcher_test main.cpp ${SRC_FILE} ${HEDER_FILES})

target_include_directories(searcher PUBLIC include src Tests include/ExeptionClasses src/ExeptionClasses)

target_include_directories(searcher_test PUBLIC include src Tests include/ExeptionClasses src/ExeptionClasses)

target_link_libraries(searcher_test PRIVATE gtest_main)
