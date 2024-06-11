#ifndef GRASSTILE_HPP
#define GRASSTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class GrassTile : public TileTypeStrategy
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
        return sf::Color(144, 238, 144);
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("barn.png");
    }

    std::vector<Resource> getImprovementCost() override
    {
        return { HumanResource(2) };
    }

    std::vector<Resource> getConstructionCost() override
    {
        return { 
            // HumanResource(30),
            // WoodResource(500),
            // MineralResource(100)
         };
    }

    std::string getName() override {
        return "Grass";
    }
};

#endif // GRASSTILE_HPP
