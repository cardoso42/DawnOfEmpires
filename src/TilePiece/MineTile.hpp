#ifndef MINETILE_HPP
#define MINETILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class MineTile : public TileTypeStrategy {
public:
    ResourceSource* createResourceSource(float amount, float generation) override {
        return new MineralResourceSource(amount, generation);
    }

    sf::Color getColor() override {
        return sf::Color(157, 157, 157);
    }

    AnimatedAsset* createDecoration() override {
        return new AnimatedAsset("mine.png", 36, { 120, 67 });
    }

    std::vector<Resource> getImprovementCost() override {
        return { HumanResource(1), WoodResource(30) };
    }

    std::vector<Resource> getConstructionCost() override {
        return { NullResource() };
    }
};

#endif // MINETILE_HPP
