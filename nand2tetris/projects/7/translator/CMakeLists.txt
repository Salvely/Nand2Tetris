CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
SET(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
project(translator)

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
        src/Parser.cpp
        src/CodeWriter.cpp
        src/main.cpp
        include/common.h)
add_executable(translator ${SOURCES})
target_include_directories(translator
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        Boost
        )

target_link_libraries(${PROJECT_NAME} "D:/Program_Files/Mingw-w64/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/lib")
