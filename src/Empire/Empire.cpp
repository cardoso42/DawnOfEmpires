#include "Empire.hpp"
#include "GameContext.hpp"

Empire::Empire() : color(sf::Color::Red), empireId(IdGenerator::GenerateEmpireId())
{
}

Empire::~Empire()
{

}

void Empire::setStartingTerritory(TilePiece *startingTile)
{
    for (auto& tile : startingTile->getNeighbors())
    {
        territory.push_back(*tile);
        tile->annexTo(empireId, color);
    }

    territory.push_back(*startingTile);
    startingTile->annexTo(empireId, color);
}

std::vector<TilePiece> Empire::getTerritory() { return territory; }
uint Empire::getId() { return empireId; }
