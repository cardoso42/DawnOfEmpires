#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "WindowManager.hpp"
#include "TilePiece.hpp"
#include "Empire.hpp"

class GameContext
{
public:
    // GameEvents enum
    enum GameEvents { GAME_STARTED, NEXT_TURN, GAME_OVER, QUIT };

    GameContext(int numPlayers, int mapSize);
    static void startGame();
    static void exitGame();
    static void nextPlayer();
    
    // Getters
    static TilePiece* getTile();
    static Empire* getPlayer();
    static int getTileHrCost();
    static std::vector<GameEvents> getEvents();
    static int getMapSize();
    static WindowManager& getWindowManager();
    static int getPlayersNumber();
    
    // Setters
    static void setNumPlayers(int numPlayers);
    static void setTile(TilePiece* newTile);
    static void setMapSize(int size);
private:
    WindowManager windowManager;
    std::vector<GameEvents> events;

    TilePiece* tile;
    std::vector<Empire> players;
    int currentPlayer;

    int mapSize;
    int playersNumber;

    static GameContext* sInstance;

    static void setPlayers(int playersNumber);
    static void verifyIfPlayerWon();
};

#endif // GAMECONTEXT_HPP
