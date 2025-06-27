cmake_minimum_required(VERSION 3.15)

project(DataStructures 
    VERSION 1.0.0
    DESCRIPTION "C++ Data Structures Library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(DataStructuresLib INTERFACE)

target_include_directories(DataStructuresLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(DataStructuresLib INTERFACE cxx_std_17)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE DataStructuresLib)

install(TARGETS main DataStructuresLib
    EXPORT DataStructuresTargets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

install(EXPORT DataStructuresTargets
    FILE DataStructuresTargets.cmake
    NAMESPACE DataStructures::
    DESTINATION lib/cmake/DataStructures
)
