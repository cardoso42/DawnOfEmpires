#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "AssetManager.hpp"
#include "TileMap.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>

class GameController
{
public:
    GameController(int id, sf::Vector2u windowSize, sf::FloatRect viewport);
    
    void updateFrame(sf::Time deltaTime);
    void drawOn(sf::RenderWindow& window, sf::Color backgroundColor = sf::Color::Black);
    
    sf::View getView();
    int getId();
private:
    sf::View view;
    int gameId;

    TileMap *map;
    TilePiece *example;

    sf::RectangleShape drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor);
};

#endif // GAME_CONTROLLER_HPP