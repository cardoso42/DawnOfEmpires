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

        return Resource(resource.name, realGeneration, resource.icon, resource.isVisible);
    }

    virtual Resource getEmptyResource() = 0;

protected:
    Resource resource;
    float generation;
};

class NullResourceSource : public ResourceSource 
{
public:
    NullResourceSource() : ResourceSource(NullResource(), 0) {}

    Resource extract(sf::Time dt) override { return NullResource(); }
    Resource getEmptyResource() override { return NullResource(); }
};

class WoodResourceSource : public ResourceSource 
{
public:
    WoodResourceSource(float amount, float generation)
        : ResourceSource(WoodResource(amount), generation) {}

    Resource getEmptyResource() override { return WoodResource(0); }
};

class MineralResourceSource : public ResourceSource 
{
public:
    MineralResourceSource(float amount, float generation)
        : ResourceSource(MineralResource(amount), generation) {}

    Resource getEmptyResource() override { return MineralResource(0); }
};

class FoodResourceSource : public ResourceSource 
{
public:
    FoodResourceSource(float amount, float generation)
        : ResourceSource(FoodResource(amount), generation) {}

    Resource getEmptyResource() override { return FoodResource(0); }
};

class TileResourceSource : public ResourceSource 
{
public:
    TileResourceSource(float amount, float generation)
        : ResourceSource(TileResource(amount), generation) {}

    Resource getEmptyResource() override { return TileResource(0); }
};

class GoldResourceSource : public ResourceSource 
{
public:
    GoldResourceSource(float amount, float generation)
        : ResourceSource(GoldResource(amount), generation) {}

    Resource getEmptyResource() override { return GoldResource(0); }
};

class CultureBonusResourceSource : public ResourceSource 
{
public:
    CultureBonusResourceSource(float amount, float generation)
        : ResourceSource(CultureBonusResource(amount), generation) {}

    Resource getEmptyResource() override { return CultureBonusResource(0); }
};

#endif // RESOURCESOURCE_HPP
