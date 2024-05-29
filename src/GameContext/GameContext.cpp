#include "GameContext.hpp"
#include <cassert>

GameContext* GameContext::sInstance = nullptr;

GameContext::GameContext()
{
    assert(sInstance == nullptr);

    sInstance = this;

    tile = nullptr;
    empire = nullptr;
}

void GameContext::setTile(TilePiece* newTile) { sInstance->tile = newTile; }
void GameContext::setEmpire(Empire* newEmpire) { sInstance->empire = newEmpire; }

Empire* GameContext::getPlayer() { return sInstance->empire; }
TilePiece* GameContext::getTile() { return sInstance->tile; }
int GameContext::getTileHrCost() { return 3; }
int GameContext::getTileImprovementHrCost() { return 1; }
