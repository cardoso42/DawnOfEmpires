#ifndef RESOURCESOURCE_HPP
#define RESOURCESOURCE_HPP

#include "Resources.hpp"
#include "SFML/Graphics.hpp"

class ResourceSource {
public:
    ResourceSource(Resource resource, float generation)
        : resource(resource), generation(generation) {}

    virtual Resource extract(sf::Time dt)
    {
        float realGeneration = std::min(resource.amount, generation * dt.asSeconds());
        resource.amount -= realGeneration;

        return Resource(resource.name, realGeneration, resource.icon);
    }

protected:
    Resource resource;
    float generation;
};

class WoodResourceSource : public ResourceSource 
{
public:
    WoodResourceSource(float amount, float generation)
        : ResourceSource(WoodResource(amount), generation) {}
};

class MineralResourceSource : public ResourceSource 
{
public:
    MineralResourceSource(float amount, float generation)
        : ResourceSource(MineralResource(amount), generation) {}
};

class FoodResourceSource : public ResourceSource 
{
public:
    FoodResourceSource(float amount, float generation)
        : ResourceSource(FoodResource(amount), generation) {}
};

#endif // RESOURCESOURCE_HPP