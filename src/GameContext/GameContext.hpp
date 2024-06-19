#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"

class GameContext
{
public:
    GameContext();
    static void nextPlayer();
    static bool isGameOver();
    
    // Getters
    static Empire* getPlayer();
    static int getTileHrCost();
    
    // Setters
    static void setPlayers(int playersNumber);
    static void setTile(TilePiece* newTile);
    static TilePiece* getTile();
private:
    TilePiece* tile;
    std::vector<Empire> players;
    int currentPlayer;
    bool gameOver;

    static GameContext* sInstance;

    static bool verifyIfPlayerWon();
};

#endif // GAMECONTEXT_HPP
