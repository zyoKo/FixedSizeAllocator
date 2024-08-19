//
// Created by Vatsalya Yadav on 8/16/24.
//

#include "SMA.pch"

#include "FixedSizeAllocator.h"

namespace CustomAllocator
{
    std::unique_ptr<FixedSizeAllocator> FixedSizeAllocator::instance{ nullptr };

    void FixedSizeAllocator::InitializeAllocator(U_INT numOfBlocks, U_INT chunkSizeInBytes)
    {
        if (!instance)
        {
            instance.reset(new FixedSizeAllocator(numOfBlocks, chunkSizeInBytes));
        }
    }

    FixedSizeAllocator& FixedSizeAllocator::GetInstance()
    {
        ASSERT(instance == nullptr, "Initialize the allocator before retriving the instance.");
        return *instance;
    }

    void FixedSizeAllocator::Allocate()
    {
        ASSERT(mainMemory != nullptr, "Main Memory is not initialized!\n");

        U_INT lastAllocatedBlock = 0;
        if (!sChunks.empty())
        {
            lastAllocatedBlock = static_cast<U_CHAR*>(sChunks.top()) - mainMemory;
        }

        U_CHAR* allocated = mainMemory + lastAllocatedBlock;
        const U_INT totalAvailableMemoryInBytes = numOfBlocks * blockSizeInBytes;

        while(allocated != (mainMemory + totalAvailableMemoryInBytes))
        {
            sChunks.push(allocated);
            allocated += blockSizeInBytes;
        }
    }

    void FixedSizeAllocator::DeAllocate(void* block)
    {
        auto* currentBlock = static_cast<unsigned char*>(block);

        // checking for memory alignment
        ASSERT((mainMemory - currentBlock) % blockSizeInBytes == 0, "Failed to deallocate block, memory alignment test failed!\n");

        // resetting the memory to 0
        memset(block, 0, mainMemory - currentBlock);

        sChunks.push(block);
    }

    void FixedSizeAllocator::Reset()
    {
        memset(&mainMemory, 0, numOfBlocks * blockSizeInBytes);

        Allocate();
    }

    void* FixedSizeAllocator::RequestChunk()
    {
        void* requestedChunk = sChunks.top();
        sChunks.pop();
        return requestedChunk;
    }

    FixedSizeAllocator::FixedSizeAllocator(U_INT numOfBlocks, U_INT chunkSizeInBytes)
        :   //lastFreeBlock(nullptr),
            numOfBlocks(numOfBlocks),
            blockSizeInBytes(chunkSizeInBytes / numOfBlocks)
    {
        mainMemory = static_cast<unsigned char*>(malloc(numOfBlocks * blockSizeInBytes));

#ifdef DEBUG
        auto memoryEnd = &mainMemory;
        memoryEnd += chunkSizeInBytes;
        std::cout << "MemAddress of Main Memory(" << &mainMemory << ", " << memoryEnd << ")\n";
#endif
    }
}

