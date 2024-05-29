#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include "TilePiece.hpp"
#include "ResourceSource.hpp"

class Empire
{
public:
    Empire();
    ~Empire();
    
    void setStartingTerritory(TilePiece *startingTile);
    void annexNewTile(TilePiece *tile);

    bool expendResources(std::vector<Resource> costs);

    std::vector<TilePiece*> getTerritory();
    std::vector<Resource> getResources();
    int getConstructionsNumber();
    uint getId();

    void update(sf::Time dt);
private:
    uint empireId;
    std::vector<TilePiece*> territory;
    std::map<std::string, Resource> resources;
    sf::Color color;

    bool canPayResource(Resource resource);
    
    class HumanResourceSource : public ResourceSource 
    {
    public:
        HumanResourceSource();
        Resource extract(sf::Time dt) override;
        void consume(std::map<std::string, Resource>& resources, sf::Time dt);
        bool activate();

    private:
        bool isUpdated;
        float consumption;

        Resource foodResource;
    };

    HumanResourceSource hrSource;
};

#endif // EMPIRE_HPP
