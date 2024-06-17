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
    
    // Setters
    static void setPlayers(int playersNumber);
    static void nextPlayer();
    static TilePiece* getTile();
    static Empire* getPlayer();
    static int getTileHrCost();
    static int getTileImprovementHrCost();
private:
    TilePiece* tile;
    std::vector<Empire> players;
    int currentPlayer;

    static GameContext* sInstance;
};

#endif // GAMECONTEXT_HPP
