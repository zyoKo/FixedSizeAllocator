//
// Created by Vatsalya Yadav on 8/16/24.
//

#include "FixedSizeAllocator.h"

#include <cassert>
#include <cstring>
#include <iostream>

namespace CustomAllocator
{
    void FixedSizeAllocator::InitializeAllocator(U_INT numOfBlocks, U_INT chunkSizeInBytes)
    {
        if (!instance)
        {
            instance = std::make_unique<FixedSizeAllocator>(numOfBlocks, chunkSizeInBytes);
        }
    }

    FixedSizeAllocator& FixedSizeAllocator::GetInstance()
    {
        // Initialize the allocator before getting the instance
        assert(instance);

        return *instance;
    }

    void* FixedSizeAllocator::Allocate()
    {
        if (!mainMemory) { return nullptr; }

        void* allocated = mainMemory;
        auto* moved = static_cast<U_CHAR*>(allocated);
        moved += blockSizeInBytes;
        lastFreeBlock = moved;
        return allocated;
    }

    void FixedSizeAllocator::DeAllocate(void* block)
    {
        auto* currentBlock = static_cast<unsigned char*>(block);

        // checking for memory alignment
        assert((mainMemory - currentBlock) % blockSizeInBytes == 0);

        // resetting the memory to 0
        memset(block, 0, blockSizeInBytes);

        // TODO: add this location to the list of pointers(maybe)
    }

    void FixedSizeAllocator::Reset()
    {
        memset(&mainMemory, 0, numOfBlocks * blockSizeInBytes);
    }

    FixedSizeAllocator::FixedSizeAllocator(U_INT numOfBlocks, U_INT chunkSizeInBytes)
        :   lastFreeBlock(nullptr),
            numOfBlocks(numOfBlocks),
            blockSizeInBytes(chunkSizeInBytes / numOfBlocks),
            numOfAvailableBlocks(numOfBlocks)
    {
        mainMemory = static_cast<unsigned char*>(malloc(numOfBlocks * blockSizeInBytes));
        lastFreeBlock = mainMemory;

#ifdef DEBUG
        auto memoryEnd = &mainMemory;
        memoryEnd += chunkSizeInBytes;
        std::cout << "MemAddress of Main Memory(" << &mainMemory << ", " << memoryEnd << ")\n";
#endif
    }
}

