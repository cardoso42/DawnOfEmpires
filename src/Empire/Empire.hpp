#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include "TilePiece.hpp"

class Empire
{
public:
    Empire();
    ~Empire();
    
    void setStartingTerritory(TilePiece *startingTile);
    std::vector<TilePiece> getTerritory();
private:
    std::vector<TilePiece> territory;

    sf::Color color;
};

#endif // EMPIRE_HPP
