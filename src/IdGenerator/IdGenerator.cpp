#include "IdGenerator.hpp"

#include <cassert>

IdGenerator* IdGenerator::mInstance = nullptr;
unsigned int IdGenerator::uniqueId = 0;
unsigned int IdGenerator::tileId = 0;

IdGenerator::IdGenerator()
{
    assert(mInstance == nullptr);

    mInstance = this;
}


unsigned int IdGenerator::GenerateUniqueId()
{
    return ++uniqueId;
}

unsigned int IdGenerator::GenerateTileId()
{
    return ++tileId;
}

