#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"

class GameContext
{
public:
    GameContext();
    
    // Getters
    static void setTile(TilePiece* newTile);
    static void setEmpire(Empire* empire);
    
    // Setters
    static TilePiece* getTile();
    static Empire* getPlayer();
    static int getTileHrCost();
    static int getTileImprovementHrCost();
private:
    TilePiece* tile;
    Empire* empire;

    static GameContext* sInstance;
};

#endif // GAMECONTEXT_HPP
