#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include "TilePiece.hpp"

class Empire
{
public:
    Empire(TilePiece& startingTile);
    ~Empire();
private:
    std::vector<TilePiece> territory;

    void setStartingTerritory(TilePiece& startingTile);
    sf::Color color;
};

#endif // EMPIRE_HPP
