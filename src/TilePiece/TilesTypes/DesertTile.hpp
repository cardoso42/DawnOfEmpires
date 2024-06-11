#ifndef DESERTTILE_HPP
#define DESERTTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class DesertTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override
    {
        return new NullResourceSource();
    }

    sf::Color getColor() override
    {
        return sf::Color(240, 230, 140);
    }

    AnimatedAsset* createDecoration() override
    {
        return nullptr;
    }

    std::vector<Resource> getImprovementCost() override
    {
        return { NullResource() };
    }

    std::vector<Resource> getConstructionCost() override
    {
        return { NullResource() };
    }

    std::string getName() override
    {
        return "Desert";
    }
};

#endif // DESERTTILE_HPP
