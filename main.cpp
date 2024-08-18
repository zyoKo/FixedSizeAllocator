#include "FixedSizeAllocator.h"

int main()
{
    CustomAllocator::FixedSizeAllocator alloc(2048, 8);

    void* acquiredMemory = alloc.Allocate(8);

    return 0;
}
