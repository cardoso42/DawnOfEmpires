#include "Empire.hpp"
#include "GameContext.hpp"

Empire::Empire() : color(sf::Color::Red), empireId(IdGenerator::GenerateEmpireId())
{
    HumanResource hr(3);
    resources[hr.getName()] = hr;
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
            if (resources.find(extractedResource.getName()) != resources.end())
            {
                resources[extractedResource.getName()] += extractedResource;
            }
            else
            {
                resources[extractedResource.getName()] = extractedResource;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    Resource hr = hrSource.extract(dt);
    resources[hr.getName()] += hr;
}

bool Empire::canPayResource(Resource resource)
{
    auto empireResource = resources.find(resource.getName());

    if (empireResource == resources.end())
    {
        return false;
    }

    float remaining = (empireResource->second - resource).getAmount();

    return remaining > 0;
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

    hrSource.activate();
}

void Empire::annexNewTile(TilePiece *newTile)
{
    for (auto& tile : territory)
    {
        if (tile->getId() == newTile->getId())
        {
            return;
        }
    }

    if (resources["Human"].getAmount() < 3)
    {
        return;
    }

    resources["Human"] -= GameContext::getTileHrCost();

    territory.push_back(newTile);
    newTile->annexTo(empireId, color);
}

bool Empire::expendResources(std::vector<Resource> costs)
{
    for (auto cost : costs)
    {
        if (!canPayResource(cost))
        {
            std::cout << "You need to improve this tile:" << std::endl;
            for (auto cost : costs)
            {
                std::cout << cost.getName() << ": " << cost.getAmount() << std::endl;
            }
            std::cout << std::endl;

            return false;
        }
    }

    for (auto cost : costs)
    {
        resources[cost.getName()] -= cost.getAmount();
    }

    return true;
}

std::vector<TilePiece*> Empire::getTerritory() { return territory; }
uint Empire::getId() { return empireId; }
