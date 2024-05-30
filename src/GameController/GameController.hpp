#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "AssetManager.hpp"
#include "GameContext.hpp"
#include "TileMap.hpp"
#include "ActionMenu.hpp"
#include "WindowManager.hpp"
#include "ResourceBar.hpp"
#include "Empire.hpp"

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

    std::vector<Empire> players;

    bool wasButtonAlreadyPressed;
    bool hasPlayerWon;

    bool verifyIfWon(Empire player);

    sf::RectangleShape drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor);
};

#endif // GAME_CONTROLLER_HPP