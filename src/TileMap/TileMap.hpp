#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "TilePiece.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class TileMap
{
public:
    TileMap(int mapRadius, sf::Vector2f center);
    void drawOn(sf::RenderWindow &window);
    void animate(sf::Time deltaTime);

private:
    std::vector<TilePiece> tiles;
    sf::Vector2i tileSize;
    int mapRadius;

    void generateHexMap(sf::Vector2f center);
};

#endif // TILEMAP_HPP
