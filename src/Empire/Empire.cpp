#include "Empire.hpp"

Empire::Empire(TilePiece &startingTile) : color(sf::Color::Red)
{
    setStartingTerritory(startingTile);
}

Empire::~Empire()
{

}

void Empire::setStartingTerritory(TilePiece &startingTile)
{
    for (auto tile : startingTile.getNeighbors())
    {
        territory.push_back(*tile);
        tile->paint(color);
    }
    territory.push_back(startingTile);
}
