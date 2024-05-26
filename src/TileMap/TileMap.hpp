#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "TilePiece.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class TileMap : public sf::Drawable
{
public:
    TileMap(int mapRadius, sf::Vector2f center);

    // Override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void animate(sf::Time deltaTime);

private:
    std::vector<TilePiece> tiles;
    int mapRadius;

    void generateHexMap(sf::Vector2f center);
};

#endif // TILEMAP_HPP
