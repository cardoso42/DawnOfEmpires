#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "AssetManager.hpp"
#include "TileMap.hpp"
#include "Window.hpp"

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
    sf::View view;
    Window window;

    TileMap *map;
    TilePiece *example;

    sf::RectangleShape drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor);
};

#endif // GAME_CONTROLLER_HPP