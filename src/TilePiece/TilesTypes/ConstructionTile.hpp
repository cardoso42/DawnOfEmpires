#ifndef CONSTRUCTIONTILE_HPP
#define CONSTRUCTIONTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class ConstructionTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override
    {
        float generation = (1 + rand() % 3) * 0.01;
        
        return new TileResourceSource(18, generation);
    }

    sf::Color getColor() override
    {
        return sf::Color(240, 230, 140);
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("pyramid.png");
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
        return "Construction";
    }
};

#endif // CONSTRUCTIONTILE_HPP
