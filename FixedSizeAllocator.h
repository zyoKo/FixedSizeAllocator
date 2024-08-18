//
// Created by Vatsalya Yadav on 8/16/24.
//

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <memory>

#include "Core.h"

//#define MAX_MEMORY 2048U
//static unsigned char MAIN_MEMORY[MAX_MEMORY];

// MainMemory: Block of data used to keep memory around until the end
// Block: MainMemory divided into blocks of bytes
// SizeOfBlock: Used as a factor to pre-compute the size of MainMemory

namespace CustomAllocator
{
    class FixedSizeAllocator
    {
    public:
        static void InitializeAllocator(U_INT numOfBlocks, U_INT chunkSizeInBytes);

        static FixedSizeAllocator& GetInstance();

        void* Allocate();

        void DeAllocate(void* block);

        void Reset();

    public:
        // Explicitly deleting all copy and move constructors because it's a singleton
        explicit FixedSizeAllocator() = delete;
        explicit FixedSizeAllocator(FixedSizeAllocator&) = delete;
        explicit FixedSizeAllocator(FixedSizeAllocator&&) = delete;
        FixedSizeAllocator& operator=(FixedSizeAllocator&) = delete;
        FixedSizeAllocator&& operator=(FixedSizeAllocator&&) = delete;

    private:
        static std::unique_ptr<FixedSizeAllocator> instance;

        U_CHAR* mainMemory;
        U_CHAR* lastFreeBlock;

        U_INT numOfBlocks;
        U_INT blockSizeInBytes;
        U_INT numOfAvailableBlocks;

        // TODO: better to divide allocationSize to (blockSize and chunkSize)
        explicit FixedSizeAllocator(U_INT numOfBlocks, U_INT chunkSizeInBytes);
    };
}

#endif //ALLOCATOR_H
