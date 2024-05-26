#include "TileMap.hpp"

#include <cmath>

TileMap::TileMap(int mapRadius, sf::Vector2f center) : mapRadius(mapRadius)
{
    generateHexMap(center);
}

void TileMap::generateHexMap(sf::Vector2f center) 
{
    sf::Vector2i tileSize = TilePiece::getSize();
    float hexWidth = tileSize.x;
    float hexRadius = hexWidth / 2.0f;
    float hexHeight = std::sqrt(3.0f) * hexRadius;

    for (int q = -mapRadius; q <= mapRadius; ++q) 
    {
        int r1 = std::max(-mapRadius, -q - mapRadius);
        int r2 = std::min(mapRadius, -q + mapRadius);

        for (int r = r1; r <= r2; ++r) 
        {
            float x = hexWidth * (q * 3.0f / 4.0f);
            float y = hexHeight * (r + q / 2.0f);
            tiles.push_back(TilePiece(x + center.x, y + center.y));
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& tile : tiles)
    {
        target.draw(tile);
    }
}

void TileMap::animate(sf::Time deltaTime)
{
    for (auto& tile : tiles)
    {
        tile.animate(deltaTime);
    }
}

void TileMap::click(int x, int y)
{
    for (auto& tile : tiles)
    {
        tile.unselect();

        if (tile.getGlobalBounds().contains({x, y}))
        {
            tile.select();
        }
    }
}
