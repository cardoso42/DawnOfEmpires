#ifndef FORESTTILE_HPP
#define FORESTTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class ForestTile : public TileTypeStrategy {
public:
    ResourceSource* createResourceSource(float amount, float generation) override {
        return new WoodResourceSource(amount, generation);
    }

    sf::Color getColor() override {
        return sf::Color(34, 139, 34);
    }

    AnimatedAsset* createDecoration() override {
        return new AnimatedAsset("tree.png");
    }

    std::vector<Resource> getImprovementCost() override {
        return { HumanResource(1) };
    }

    std::vector<Resource> getConstructionCost() override {
        return { NullResource() };
    }
};

#endif // FORESTTILE_HPP
