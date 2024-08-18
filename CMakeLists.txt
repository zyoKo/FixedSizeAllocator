cmake_minimum_required(VERSION 3.28)
project(SmallMemoryAllocator)

set(CMAKE_CXX_STANDARD 17)

add_executable(SmallMemoryAllocator main.cpp
        FixedSizeAllocator.h
        FixedSizeAllocator.cpp
        Core.h)
