#ifndef FORESTTILE_HPP
#define FORESTTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class ForestTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override
    {
        float amount = 500 + rand() % 1000;
        float generation = .95 + rand() % 10 * 0.01;

        return new WoodResourceSource(amount, generation);
    }

    sf::Color getColor() override
    {
        return sf::Color(34, 139, 34);
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("chop_tree.png", 7, {50, 92}, sf::seconds(3));
    }

    AnimatedAsset* createEmptyDecoration() override
    {
        return new AnimatedAsset("dead-tree.png");
    }

    std::vector<Resource> getImprovementCost() override
    {
        return { HumanResource(1) };
    }

    std::vector<Resource> getConstructionCost() override
    {
        return { NullResource() };
    }

    std::string getName() override
    {
        return "Forest";
    }
};

#endif // FORESTTILE_HPP
