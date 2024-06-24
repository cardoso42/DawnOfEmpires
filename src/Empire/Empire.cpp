#include "Empire.hpp"
#include "GameContext.hpp"

#include <cmath>

Empire::Empire(sf::Color empireColor) : color(empireColor), constructions(0),
    empireId(IdGenerator::GenerateEmpireId()), won(false), lastSelectedTile(nullptr)
{
    HumanResource hr(3);
    FoodResource food(10);
    
    resources[hr.getName()] = hr;
    resources[food.getName()] = food;
    resources[TileResource(0).getName()] = TileResource(0);

    started = false;
}

Empire::~Empire()
{

}

void Empire::setLastSelectedTile(TilePiece *tile) { lastSelectedTile = tile; }

TilePiece *Empire::getLastSelectedTile() { return lastSelectedTile; }

void Empire::update(sf::Time dt)
{
    turnResources.clear();

    for (auto& tile : territory)
    {
        try
        {
            Resource extractedResource = tile->extractResource(dt);
            addResource(extractedResource);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    turnResources[FoodResource(0).getName()] -= hrSource.consume(resources, dt);
    Resource hr = hrSource.extract(dt);
    resources[hr.getName()] += hr;
    turnResources[hr.getName()] = hr;
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
    if (newTile->isOwnedBy(empireId))
    {
        return;
    }

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
    auto resourcesVector = mapToVector(resources);
    std::vector<Resource> returnVector;

    for (auto resource : resourcesVector)
    {
        if (resource.getVisibility() && resource.getAmount() >= 0.1)
        {
            returnVector.push_back(resource);
        }
    }

    return returnVector;
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

    if (newResource.getVisibility())
    {
        auto it = turnResources.find(newResource.getName());
        if (it != turnResources.end())
        {
            it->second += newResource;
        }
        else
        {
            turnResources[newResource.getName()] = newResource;
        }
    }
}

void Empire::abandonGame()
{
    resources.clear();

    for (auto tile : territory)
    {
        tile->annexTo(-1, sf::Color::Transparent);
    }
}

void Empire::setAsWinner() { won = true; }

bool Empire::haveWon() { return won; }

bool Empire::haveStarted()
{
    return started;
}

int Empire::getConstructionsNumber() { return constructions; }

void Empire::setStartingTerritory(TilePiece *startingTile)
{
    std::unordered_set<TilePiece*> territorySet;
    std::unordered_set<TilePiece*> neighborsSet;

    for (auto& tile : startingTile->getNeighbors())
    {
        territory.push_back(tile);
        tile->annexTo(empireId, color);
    }

    startingTile->annexTo(empireId, color);
    territory.push_back(startingTile);
    territorySet.insert(startingTile);

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
    started = true;
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

void Empire::removeTile(TilePiece* tile)
{
    for (auto it = territory.begin(); it != territory.end(); it++)
    {
        if ((*it)->getId() == tile->getId())
        {
            territory.erase(it);
            break;
        }
    }

    for (auto neighbor : tile->getNeighbors())
    {
        bool stillIsNeighbor = false;

        for (auto neighborNeighbor : neighbor->getNeighbors())
        {
            if (neighborNeighbor->isOwnedBy(empireId))
            {
                stillIsNeighbor = true;
                break;
            }
        }

        if (!stillIsNeighbor)
        {
            neighbors.erase(neighbor);
        }
    }
}

void Empire::createNewConstruction(TilePiece *tile, TilePiece::ConstructionType type)
{
    if (tile->isConstructable() && expendResources(tile->getConstructionCost()))
    {
        tile->construct(type);
        constructions++;

        if (type == TilePiece::ConstructionType::CULTURE)
        {
            auto neighbors = tile->getNeighbors();
            for (auto neighbor : neighbors)
            {
                neighbor->addBonus(tile->extractResource(sf::seconds(5)).getAmount());
            }
        }
        else if (type == TilePiece::ConstructionType::MILITARY)
        {
            auto neighbors = tile->getNeighbors();
            int counter{0};
            for (auto neighbor : neighbors)
            {
                if (!neighbor->isOwnedBy(empireId))
                {
                    addTileToTerritory(neighbor);
                }

                auto neighborNeighbors = neighbor->getNeighbors();
                int countercounter{0};
                for (auto neighborNeighbor : neighborNeighbors)
                {
                    if (!neighborNeighbor->isOwnedBy(empireId))
                    {
                        addTileToTerritory(neighborNeighbor);
                    }
                }
            }
        }
    }
}

bool Empire::expendResources(std::vector<Resource> costs)
{
    if (!hasResources(costs))
    {
        return false;
    }

    for (auto cost : costs)
    {
        resources[cost.getName()] -= cost.getAmount();
    }

    return true;
}

bool Empire::hasResources(std::vector<Resource> resources)
{
    for (auto resource : resources)
    {
        if (!canPayResource(resource))
        {
            return false;
        }
    }

    return true;
}

bool Empire::isTileNeighbor(TilePiece *tile)
{
    for (auto neighbor : neighbors)
    {
        if (neighbor->getId() == tile->getId())
        {
            return true;
        }
    }

    return false;
}

std::map<std::string, Resource> Empire::getTurnResources() { return turnResources; }
std::vector<TilePiece*> Empire::getTerritory() { return territory; }
uint Empire::getId() { return empireId; }
sf::Color Empire::getColor() { return color; }

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

float Empire::HumanResourceSource::consume(std::map<std::string, Resource>& resources, sf::Time dt)
{
    if (resources.find("Food") == resources.end())
    {
        consumption = 0;
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

    return consumption * dt.asSeconds();
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

template <typename T>
inline std::vector<T> Empire::mapToVector(const std::map<std::string, T> &inputMap)
{
    std::vector<T> returnVector;

    for (auto it = inputMap.begin(); it != inputMap.end(); it++)
    {
        returnVector.push_back(it->second);
    }

    return returnVector;
}
