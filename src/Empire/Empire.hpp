#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include "TilePiece.hpp"
#include "ResourceSource.hpp"

class ResourceSource;

class HumanResourceSource : public ResourceSource 
{
public:
    HumanResourceSource(float generation)
        : ResourceSource(HumanResource(3), generation) {}

    Resource extract(sf::Time dt) override 
    {
        float realGeneration = generation * resource.getAmount() * dt.asSeconds();
        return Resource(resource.getName(), realGeneration, resource.getIcon());
    }
};

class Empire
{
public:
    Empire();
    ~Empire();
    
    void setStartingTerritory(TilePiece *startingTile);
    void annexNewTile(TilePiece *tile);
    std::vector<TilePiece*> getTerritory();
    std::vector<Resource> getResources();
    void update(sf::Time dt);
    uint getId();
private:
    uint empireId;
    std::vector<TilePiece*> territory;
    std::map<std::string, Resource> resources;
    sf::Color color;

    HumanResource hr;
    HumanResourceSource hrSource;
};

#endif // EMPIRE_HPP
