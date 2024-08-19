cmake_minimum_required(VERSION 3.28)

project(SmallMemoryAllocator)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    MESSAGE("Apple System Detected")
    set(CMAKE_C_COMPILER "/usr/bin/gcc")
    set(CMAKE_CXX_COMPILER "/usr/bin/g++")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    MESSAGE("Windows System Detected")
    set(CMAKE_C_COMPILER "MSVC")
    set(CMAKE_CXX_COMPILER "MSVC")
endif()

# add definitions based on compiler used
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    MESSAGE(STATUS "GCC Compiler Detected")
    add_definitions(-DGCC_COMPILER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")  # Enable all warnings in GCC
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    MESSAGE(STATUS "MSVC Compiler Detected")
    add_definitions(-DMSVC_COMPILER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4")  # Enable all warnings in MSVC
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    MESSAGE(STATUS "Clang Compiler Detected")
else()
    MESSAGE(STATUS "Suitable compiler not found. Only support for GCC and MSVC.")
endif()

# Build Types
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    MESSAGE(STATUS "Debug Configuration Enabled")
    add_definitions(-DDEBUG_MODE -DASSERT_CHECK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")    # enable debug symbols
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    MESSAGE(STATUS "Release Configuration Enabled")
    add_definitions(-DRELEASE_MODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")   # optimize for speed
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    MESSAGE(STATUS "ReleaseWithDebugInfo Configuration Enabled")
    add_definitions(-DRELEASE_WITH_DEB_INFO -DLOG_CHECK)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g")    #Optimize with Debug Info
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    MESSAGE(STATUS "MinimumSizeRelease Configuration Enabled")
    add_definitions(-DMIN_SIZE_REL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")    #Optimize with Debug Info
else()
    MESSAGE(STATUS "Unknown Build Type - ERROR")
endif()

#Files to compile and build
add_executable(SmallMemoryAllocator main.cpp
        FixedSizeAllocator.h
        FixedSizeAllocator.cpp
        Core.h)

# Pre-compiled header(s)
target_precompile_headers(SmallMemoryAllocator
        PUBLIC
        SMA.pch)
