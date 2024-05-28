#include "Empire.hpp"
#include "GameContext.hpp"

Empire::Empire() : color(sf::Color::Red), empireId(IdGenerator::GenerateEmpireId())
{
}

Empire::~Empire()
{

}

void Empire::update(sf::Time dt)
{
    for (auto& tile : territory)
    {
        try
        {
            Resource extractedResource = tile->extractResource(dt);
            if (resources.find(extractedResource.name) != resources.end())
            {
                resources[extractedResource.name] += extractedResource;
            }
            else
            {
                resources[extractedResource.name] = extractedResource;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

std::vector<Resource> Empire::getResources()
{
    std::vector<Resource> returnResources;

    for (auto it = resources.begin(); it != resources.end(); it++)
    {
        returnResources.push_back(it->second);
    }

    return returnResources;
}

void Empire::setStartingTerritory(TilePiece *startingTile)
{
    for (auto& tile : startingTile->getNeighbors())
    {
        territory.push_back(tile);
        tile->annexTo(empireId, color);
    }

    territory.push_back(startingTile);
    startingTile->annexTo(empireId, color);
}

std::vector<TilePiece*> Empire::getTerritory() { return territory; }
uint Empire::getId() { return empireId; }
