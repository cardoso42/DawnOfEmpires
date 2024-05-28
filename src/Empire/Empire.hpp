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
    uint getId();
private:
    uint empireId;
    std::vector<TilePiece> territory;

    sf::Color color;
};

#endif // EMPIRE_HPP
