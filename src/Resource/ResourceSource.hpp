#ifndef RESOURCESOURCE_HPP
#define RESOURCESOURCE_HPP

#include "Resources.hpp"
#include "SFML/Graphics.hpp"

struct ResourceSource {
    Resource resource;
    float generation;

    ResourceSource(Resource resource, float generation)
        : resource(resource), generation(generation) {}

    Resource extract(sf::Time dt)
    {
        float realGeneration = std::min(resource.amount, generation * dt.asSeconds());
        resource.amount -= realGeneration;

        return Resource(resource.name, realGeneration, resource.icon);
    }
};

struct WoodResourceSource : public ResourceSource {
    WoodResourceSource(float amount, float generation)
        : ResourceSource(WoodResource(amount), generation) {}
};

struct MineralResourceSource : public ResourceSource {
    MineralResourceSource(float amount, float generation)
        : ResourceSource(MineralResource(amount), generation) {}
};

struct FoodResourceSource : public ResourceSource {
    FoodResourceSource(float amount, float generation)
        : ResourceSource(FoodResource(amount), generation) {}
};

#endif // RESOURCESOURCE_HPP