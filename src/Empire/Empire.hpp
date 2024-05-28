#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include "TilePiece.hpp"

class Empire
{
public:
    Empire();
    ~Empire();
    
    void setStartingTerritory(TilePiece *startingTile);
    std::vector<TilePiece*> getTerritory();
    std::vector<Resource> getResources();
    void update(sf::Time dt);
    uint getId();
private:
    uint empireId;
    std::vector<TilePiece*> territory;
    std::map<std::string, Resource> resources;
    sf::Color color;
};

#endif // EMPIRE_HPP
