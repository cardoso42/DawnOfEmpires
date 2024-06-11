#ifndef CONSTRUCTIONTILE_HPP
#define CONSTRUCTIONTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class ConstructionTile : public TileTypeStrategy
{
public:
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
};

class MilitaryConstructionTile : public ConstructionTile
{
public:
    ResourceSource* createResourceSource() override
    {
    #ifdef DEBUG
        float generation = 0.25;
    #else
        float generation = (1 + rand() % 3) * 0.01;
    #endif

        return new TileResourceSource(18, generation);
    }

    std::string getName() override
    {
        return "Military Construction";
    }
};

class EconomyConstructionTile : public ConstructionTile
{
public:
    ResourceSource* createResourceSource() override
    {
    #ifdef DEBUG
        float generation = 1;
    #else
        float generation = (1 + rand() % 3) * 0.01;
    #endif
        
        return new GoldResourceSource(5, generation);
    }

    std::string getName() override
    {
        return "Economy Construction";
    }
};

class CultureConstructionTile : public ConstructionTile
{
public:
    ResourceSource* createResourceSource() override
    {
        float generation = (1 + rand() % 10) * 0.1;
        return new CultureBonusResourceSource(rand() % 50 + 50, generation);
    }

    std::string getName() override
    {
        return "Culture Construction";
    }
};

#endif // CONSTRUCTIONTILE_HPP
