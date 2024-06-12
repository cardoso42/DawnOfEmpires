#include "Empire.hpp"
#include "GameContext.hpp"

#include <cmath>

Empire::Empire() : color(sf::Color::Red), constructions(0),
    empireId(IdGenerator::GenerateEmpireId())
{
    HumanResource hr(3);
    FoodResource food(10);
    
    resources[hr.getName()] = hr;
    resources[food.getName()] = food;
    resources[TileResource(0).getName()] = TileResource(0);
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

            if (extractedResource.getName() == CultureBonusResource(0).getName())
            {
                for (auto& neighbor : tile->getNeighbors())
                {
                    if (!neighbor->isOwnedBy(empireId))
                    {
                        continue;
                    }

                    Resource bonusResourceModel = neighbor->getEmptyResource();

                    if (bonusResourceModel.getName() == NullResource().getName())
                    {
                        continue;
                    }

                    Resource bonusResource = Resource(
                        bonusResourceModel.getName(), 
                        extractedResource.getAmount(), 
                        bonusResourceModel.getIcon(), 
                        bonusResourceModel.getVisibility()
                    );

                    addResource(bonusResource);
                }
                continue;
            }

            addResource(extractedResource);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    hrSource.consume(resources, dt);
    Resource hr = hrSource.extract(dt);
    resources[hr.getName()] += hr;

    if (resources[TileResource(0).getName()].getAmount() >= 1)
    {
        int index = std::rand() % neighbors.size();

        auto neighborsVector = std::vector<TilePiece*>(neighbors.begin(), neighbors.end());
        TilePiece* newTile = neighborsVector[index];

        addTileToTerritory(newTile);

        resources[TileResource(0).getName()] -= 1;
    }
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

void Empire::addTileToTerritory(TilePiece *newTile)
{
    territory.push_back(newTile);
    newTile->annexTo(empireId, color);

    neighbors.erase(newTile);
    
    for (auto& tile : newTile->getNeighbors())
    {
        if (tile->isOwnedBy(empireId))
        {
            continue;
        }

        neighbors.insert(tile);
    }
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

void Empire::addResource(Resource newResource)
{
    if (resources.find(newResource.getName()) != resources.end())
    {
        resources[newResource.getName()] += newResource;
    }
    else
    {
        resources[newResource.getName()] = newResource;
    }
}

int Empire::getConstructionsNumber() { return constructions; }

void Empire::setStartingTerritory(TilePiece *startingTile)
{
    for (auto& tile : startingTile->getNeighbors())
    {
        territory.push_back(tile);
        tile->annexTo(empireId, color);
    }

    territory.push_back(startingTile);
    startingTile->annexTo(empireId, color);

    std::unordered_set<TilePiece*> territorySet;
    std::unordered_set<TilePiece*> neighborsSet;

    for (auto& tile : startingTile->getNeighbors())
    {
        territorySet.insert(tile);
    }

    for (auto& tile : startingTile->getNeighbors())
    {
        for (auto& neighboringTile : tile->getNeighbors())
        {
            if (territorySet.find(neighboringTile) == territorySet.end() &&
                neighborsSet.find(neighboringTile) == neighborsSet.end())
            {
                neighborsSet.insert(neighboringTile);
                neighbors.insert(neighboringTile);
            }
        }
    }

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

    addTileToTerritory(newTile);
}

void Empire::createNewConstruction(TilePiece *tile, TilePiece::ConstructionType type)
{
    if (tile->isConstructable() && expendResources(tile->getConstructionCost()))
    {
        tile->construct(type);
        constructions++;
    }
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

        if (resources["Food"].getAmount() < 0)
        {
            resources["Food"] = FoodResource(0);
        }
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
