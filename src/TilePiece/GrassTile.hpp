#ifndef GRASSTILE_HPP
#define GRASSTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class GrassTile : public TileTypeStrategy {
public:
    ResourceSource* createResourceSource(float amount, float generation) override {
        return new FoodResourceSource(amount, generation);
    }

    sf::Color getColor() override {
        return sf::Color(144, 238, 144);
    }

    AnimatedAsset* createDecoration() override {
        return new AnimatedAsset("grass.png");
    }

    std::vector<Resource> getImprovementCost() override {
        return { HumanResource(2) };
    }

    std::vector<Resource> getConstructionCost() override {
        return { 
            HumanResource(30),
            WoodResource(500),
            MineralResource(100)
         };
    }
};

#endif // GRASSTILE_HPP
