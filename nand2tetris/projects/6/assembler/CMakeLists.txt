cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)

#set(CMAKE_FIND_LIBRARY_PREFIXES C:/Program Files/Boost/boost_1_84_0/boost)
project(assembler)
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/Boost/boost_1_84_0")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/Boost/boost_1_84_0")
SET(Boost_INCLUDE_DIR "C:/Program Files/Boost/boost_1_84_0")
set(BOOST_ROOT C:/Program_Files/boost_1_84_0)

find_package(Boost)
if(Boost_FOUND)
    message ("boost found")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message (FATAL_ERROR "Cannot find Boost")
endif()

set(SOURCES
    src/parser.cpp
    src/codegen.cpp
    src/symbol_table.cpp
    src/main.cpp
)
add_executable(assembler ${SOURCES})
target_include_directories(assembler
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        Boost
)

target_link_libraries(${PROJECT_NAME} "D:/Program_Files/Mingw-w64/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/lib")


