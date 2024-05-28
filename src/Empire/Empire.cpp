#include "Empire.hpp"

Empire::Empire() : color(sf::Color::Red)
{
}

Empire::~Empire()
{

}

void Empire::setStartingTerritory(TilePiece *startingTile)
{
    std::cout << startingTile << std::endl;
    for (auto& tile : startingTile->getNeighbors())
    {
        territory.push_back(*tile);
        tile->paint(color);
    }
    territory.push_back(*startingTile);
    startingTile->paint(color);
}

std::string Empire::getName() { return "Funcionou!"; }
