#include "IdGenerator.hpp"

#include <cassert>

IdGenerator* IdGenerator::mInstance = nullptr;

IdGenerator::IdGenerator()
{
    assert(mInstance == nullptr);
    
    mInstance = this;
}


