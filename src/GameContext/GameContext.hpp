#ifndef GAMECONTEXT_HPP
#define GAMECONTEXT_HPP

#include "WindowManager.hpp"
#include "TilePiece.hpp"
#include "Empire.hpp"

#include <unordered_map>

#define CallbackFunction std::function<void(std::vector<void*>)>

class GameContext
{
public:
    // GameEvents enum
    enum GameEvents { GAME_STARTED, NEXT_TURN, GAME_OVER, MAIN_MENU, QUIT, PAUSE, RESUME };

    GameContext(int numPlayers, int mapSize);
    static void startGame();
    static void nextPlayer();
    static void playSound(sf::SoundBuffer &buffer);
    static void addKeyAction(sf::Keyboard::Key key, CallbackFunction action);
    static void removeKeyAction(sf::Keyboard::Key key);
    static void clearKeyActions();
    static void clearAlphanumericKeyActions();
    static void clearDirectionalKeyActions();
    static void notifyEvent(GameEvents event);
    
    // Getters
    static TilePiece* getTile();
    static Empire* getPlayer();
    static Empire getWinnerPlayer();
    static int getTileHrCost();
    static std::vector<GameEvents> getEvents();
    static int getMapSize();
    static WindowManager& getWindowManager();
    static int getPlayersNumber();
    static int getMaxPlayersNumber();
    static int getMaxMapSize();
    static std::unordered_map<sf::Keyboard::Key, CallbackFunction> getKeyActions();
    
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
    sf::Sound soundEffect;

    int mapSize;
    int playersNumber;
    static const std::vector<sf::Color> colors;

    std::unordered_map<sf::Keyboard::Key, CallbackFunction> keyActions;

    static GameContext* sInstance;

    static void setPlayers(int playersNumber);
    static void verifyIfPlayerWon();
};

#endif // GAMECONTEXT_HPP
