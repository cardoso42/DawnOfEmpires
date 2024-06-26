#ifndef CONSTRUCTIONTILE_HPP
#define CONSTRUCTIONTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

#include <limits>

class ConstructionTile : public TileTypeStrategy
{
public:
    sf::Color getColor() override
    {
        return sf::Color(255, 192, 203);
    }

    AnimatedAsset* createEmptyDecoration() override
    {
        return createDecoration();
    }

    std::vector<Resource> getImprovementCost() override
    {
        return { NullResource() };
    }

    std::vector<Resource> getConstructionCost() override
    {
        return { NullResource() };
    }

    sf::SoundBuffer &getSoundBuffer() override
    {
        return AssetManager::GetSoundBuffer("construction.mp3");
    }
};

class MilitaryConstructionTile : public ConstructionTile
{
public:
    ResourceSource* createResourceSource() override
    {
        return new NullResourceSource();
    }

    std::string getName() override
    {
        return "Military Construction";
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("arc-de-triomphe.png");
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

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("bank.png");
    }
};

class CultureConstructionTile : public ConstructionTile
{
public:
    ResourceSource* createResourceSource() override
    {
        float generation = (1 + rand() % 3) * 0.01;
        return new CultureBonusResourceSource(std::numeric_limits<float>::max(), generation);
    }

    std::string getName() override
    {
        return "Culture Construction";
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("pisa.png");
    }
};

#endif // CONSTRUCTIONTILE_HPP
