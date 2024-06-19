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
    WindowManager windowManager;

    ResourceBar *bar;
    ActionMenu *menu;
    TileMap *map;
    HelpArea *help;

    bool wasMouseButtonAlreadyPressed;
    int numPlayers;

    sf::Keyboard::Key currentPressedKey;
    sf::Keyboard::Key lastVerticalDirectionKey;

    std::unordered_map<sf::Keyboard::Key, std::function<void()>> directionalActions;
    std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyActions;

    void handleMouseInput();
    void handleKeyboardInput();

    sf::RectangleShape drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor);
};

#endif // GAME_CONTROLLER_HPP