#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "AssetManager.hpp"
#include "GameContext.hpp"
#include "TileMap.hpp"
#include "ActionMenu.hpp"
#include "WindowManager.hpp"
#include "ResourceBar.hpp"
#include "Empire.hpp"
#include "HelpArea.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <MainMenu.hpp>
#include <BaseComponent.hpp>

class GameController
{
public:
    GameController();
    ~GameController();

    void handleInput();
    void updateFrame(sf::Time deltaTime);
    void render(sf::Color backgroundColor = sf::Color::Black);
    
    bool isOver();
private:
    enum State { MAIN_MENU, GAME_RUNNING, PAUSE_MENU, WINNER_SCREEN };

    WindowManager* windowManager;

    bool wasMouseButtonAlreadyPressed;
    State currentState;

    sf::Keyboard::Key currentPressedKey;

    std::unordered_map<std::string, BaseComponent*> components;
    std::unordered_map<std::string, BaseComponent*> savedComponents;
    bool musicPlayingWhenPaused;

    sf::Music music;

    void clearComponents();
    void saveCurrentComponents();
    void restoreSavedComponents();
    void clearSavedComponents();

    void handleMouseInput();
    void handleKeyboardInput();
    void handleGameOver();
    void handleGameStarted();
    void handleNextTurn();
    void handleGameQuit();
    void handleMainMenu();
    void handleGamePaused();
    void handleGameResumed();

    void addEscapeKeybinding();

    sf::RectangleShape drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor);
};

#endif // GAME_CONTROLLER_HPP