#ifndef WATERTILE_HPP
#define WATERTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class WaterTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override
    {
        float amount = 5000 + rand() % 10000;
        float generation = .95 + rand() % 10 * 0.01;
        
        return new FoodResourceSource(amount, generation);
    }

    sf::Color getColor() override
    {
        return sf::Color(135,206,250);
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("fish.png", 72, { 80, 70 });
    }

    std::vector<Resource> getImprovementCost() override
    {
        return { HumanResource(1), WoodResource(30) };
    }

    std::vector<Resource> getConstructionCost() override
    {
        return { NullResource() };
    }

    std::string getName() override
    {
        return "Water";
    }
};

#endif // WATERTILE_HPP
