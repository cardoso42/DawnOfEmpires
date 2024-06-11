#ifndef TILETYPESTRATEGY_HPP
#define TILETYPESTRATEGY_HPP

#include "ResourceSource.hpp"
#include "AnimatedAsset.hpp"
#include <SFML/Graphics.hpp>
#include <stdexcept>

class TileTypeStrategy {
public:
    virtual ~TileTypeStrategy() = default;
    virtual ResourceSource* createResourceSource() = 0;
    virtual sf::Color getColor() = 0;
    virtual AnimatedAsset* createDecoration() = 0;
    virtual std::vector<Resource> getImprovementCost() = 0;
    virtual std::vector<Resource> getConstructionCost() = 0;
    virtual std::string getName() = 0;
};

#endif // TILETYPESTRATEGY_HPP
