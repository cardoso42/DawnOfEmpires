#ifndef TILETYPESTRATEGYFACTORY_HPP
#define TILETYPESTRATEGYFACTORY_HPP

#include "TileTypeStrategy.hpp"
#include "TilesTypes/ForestTile.hpp"
#include "TilesTypes/MineTile.hpp"
#include "TilesTypes/GrassTile.hpp"
#include "TilesTypes/DesertTile.hpp"
#include "TilesTypes/WaterTile.hpp"
#include "TilesTypes/ConstructionTile.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <random>

class TileTypeStrategyFactory 
{
public:
    TileTypeStrategyFactory() 
    {
        std::random_device rd;
        gen = std::mt19937(rd());
        dis = std::uniform_int_distribution<>(0, 4);
    }

    TileTypeStrategy* createRandomStrategy() 
    {
        int type = dis(gen);

        switch (type)
        {
        case 0:
            return new ForestTile();
        case 1:
            return new MineTile();
        case 2:
            return new GrassTile();
        case 3:
            return new DesertTile();
        case 4:
            return new WaterTile();
        default:
            throw std::logic_error("Invalid tile type");
        }
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

#endif // TILETYPESTRATEGYFACTORY_HPP
