#ifndef WATERTILE_HPP
#define WATERTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class WaterTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override
    {
        float amount = 150 + rand() % 50;
        float generation = .95 + rand() % 10 * 0.01;
        
        return new FoodResourceSource(amount, generation);
    }

    sf::Color getColor() override
    {
        return sf::Color(135,206,250);
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("Fisherman_hook.png", 6, { 48, 48 }, sf::seconds(1));
    }

    AnimatedAsset* createEmptyDecoration() override
    {
        return new AnimatedAsset("polluted.png");
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

    sf::SoundBuffer &getSoundBuffer() override
    {
        return AssetManager::GetSoundBuffer("water-walk.mp3");
    }
};

#endif // WATERTILE_HPP
