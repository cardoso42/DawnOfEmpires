#ifndef GRASSTILE_HPP
#define GRASSTILE_HPP

#include "TileTypeStrategy.hpp"
#include "Resources.hpp"

class GrassTile : public TileTypeStrategy
{
public:
    ResourceSource* createResourceSource() override
    {
        float amount = 200 + rand() % 50;
        float generation = .95 + rand() % 10 * 0.01;

        return new FoodResourceSource(amount, generation);
    }

    sf::Color getColor() override
    {
        return sf::Color(144, 238, 144);
    }

    AnimatedAsset* createDecoration() override
    {
        const std::vector<std::string> crops = {
            "Carrot", "Onion", "Potato", "Radish", "Spinach", "Turnip"
        };
        int randomCrop = rand() % crops.size();

        return new AnimatedAsset(crops[randomCrop] + ".png", 3, {33, 40}, sf::seconds(3));
    }

    AnimatedAsset* createEmptyDecoration() override
    {
        return new AnimatedAsset("dry-dirt.png");
    }

    std::vector<Resource> getImprovementCost() override
    {
        return { HumanResource(2) };
    }

    std::vector<Resource> getConstructionCost() override
    {
#ifdef DEBUG
        return { };
#else
        return { 
            HumanResource(30),
            WoodResource(500),
            MineralResource(100)
        };
#endif
    }

    std::string getName() override {
        return "Grass";
    }

    sf::SoundBuffer &getSoundBuffer() override
    {
        return AssetManager::GetSoundBuffer("cow.mp3");
    }
};

#endif // GRASSTILE_HPP
