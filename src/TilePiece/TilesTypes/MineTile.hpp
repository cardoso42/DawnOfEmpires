#ifndef MINETILE_HPP
#define MINETILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class MineTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override 
    {
        float amount = 100 + rand() % 200;
        float generation = .95 + rand() % 10 * 0.01;
        
        return new MineralResourceSource(amount, generation);
    }

    sf::Color getColor() override
    {
        return sf::Color(157, 157, 157);
    }

    AnimatedAsset* createDecoration() override
    {
        return new AnimatedAsset("Mine.png", 19, { 181, 147 }, sf::seconds(2));
    }

    AnimatedAsset* createEmptyDecoration() override
    {
        return new AnimatedAsset("empty-mine.png");
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
        return "Mine";
    }

    sf::SoundBuffer &getSoundBuffer() override
    {
        return AssetManager::GetSoundBuffer("mine.mp3");
    }
};

#endif // MINETILE_HPP
