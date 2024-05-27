#include "Empire.hpp"

Empire::Empire() : color(sf::Color::Red)
{
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
