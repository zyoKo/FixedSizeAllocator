//
// Created by Vatsalya Yadav on 8/16/24.
//

#include "FixedSizeAllocator.h"

int main()
{
    CustomAllocator::FixedSizeAllocator::InitializeAllocator(2048, 8);

    auto& allocator = CustomAllocator::FixedSizeAllocator::GetInstance();
    allocator.Allocate();

    return 0;
}
