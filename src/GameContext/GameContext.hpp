#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"

class GameContext
{
public:
    // GameEvents enum
    enum GameEvents { GAME_STARTED, NEXT_TURN, GAME_OVER };

    GameContext();
    static void startGame();
    static void nextPlayer();
    
    // Getters
    static Empire* getPlayer();
    static int getTileHrCost();
    static std::vector<GameEvents> getEvents();
    static int getMapSize();
    
    // Setters
    static void setPlayers(int playersNumber);
    static void setTile(TilePiece* newTile);
    static TilePiece* getTile();
private:
    TilePiece* tile;
    std::vector<GameEvents> events;
    std::vector<Empire> players;
    int currentPlayer;

    static GameContext* sInstance;

    static void verifyIfPlayerWon();
};

#endif // GAMECONTEXT_HPP
