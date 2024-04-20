CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
SET(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER g++)
#add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
project(Jack_Analyzer)

#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "C:/Program Files/Boost/boost_1_84_0")
#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "C:/Program Files/Boost/boost_1_84_0")
#SET(Boost_INCLUDE_DIR "C:/Program Files/Boost/boost_1_84_0")
#set(BOOST_ROOT C:/Program_Files/boost_1_84_0)

find_package(Boost REQUIRED COMPONENTS filesystem)
if (Boost_FOUND)
    message("boost found")
    include_directories(${Boost_INCLUDE_DIRS})
else ()
    message(FATAL_ERROR "Cannot find Boost")
endif ()

set(SOURCES
        src/JackTokenizer.cpp
        src/CompilationEngine.cpp
        src/common.cpp
        src/main.cpp
        src/SymbolTable.cpp src/VMWriter.cpp include/VMWriter.h src/CodeGen.cpp include/CodeGen.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
