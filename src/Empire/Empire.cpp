#include "Empire.hpp"
#include "GameContext.hpp"

#include <cmath>

Empire::Empire() : color(sf::Color::Red), empireId(IdGenerator::GenerateEmpireId())
{
    HumanResource hr(3);
    FoodResource food(10);
    
    resources[hr.getName()] = hr;
    resources[food.getName()] = food;
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

    hrSource.consume(resources, dt);
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

    return remaining >= 0;
}

std::vector<Resource> Empire::getResources()
{
    std::vector<Resource> returnResources;

    for (auto it = resources.begin(); it != resources.end(); it++)
    {
        if (it->second.getVisibility())
        {
            returnResources.push_back(it->second);
        }
    }

    return returnResources;
}

int Empire::getConstructionsNumber()
{
    // TODO: store the number of constructions in the Empire class
    int count{0};

    for (auto& tile : territory)
    {
        if (tile->isConstruction())
        {
            count++;
        }
    }

    return count;
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

    if (resources["Human"].getAmount() < GameContext::getTileHrCost())
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

// HumanResourceSource implementation
Empire::HumanResourceSource::HumanResourceSource() : isUpdated(false), consumption(0),
    ResourceSource(HumanResource(0), 0), foodResource(FoodResource(10)) {}

Resource Empire::HumanResourceSource::extract(sf::Time dt)
{
    if (!isUpdated)
    {
        throw std::logic_error("To call extract on HumanResourceSource you should first call consume");
    }

    isUpdated = false;

    float realGeneration = generation * foodResource.getAmount() * dt.asSeconds();
    
    resource += realGeneration;

    return Resource(resource.getName(), realGeneration, resource.getIcon());
}

void Empire::HumanResourceSource::consume(std::map<std::string, Resource>& resources, sf::Time dt)
{
    if (resources.find("Food") == resources.end())
    {
        foodResource = FoodResource(0);
    }
    else
    {
        foodResource = resources["Food"];
        consumption = 0.1 * resource.getAmount();
        resources["Food"] -= consumption * dt.asSeconds();
    }

    isUpdated = true;
}

bool Empire::HumanResourceSource::activate()
{
    if (generation == 0)
    {
        generation = 0.01;
        return true;
    }

    return false;
}
