#ifndef EMPIRE_HPP
#define EMPIRE_HPP

#include "TilePiece.hpp"
#include "ResourceSource.hpp"
#include <unordered_set>

class Empire
{
public:
    Empire(sf::Color empireColor);
    ~Empire();

    void setStartingTerritory(TilePiece *startingTile);
    void annexNewTile(TilePiece *tile);
    void createNewConstruction(TilePiece *tile, TilePiece::ConstructionType type);

    bool expendResources(std::vector<Resource> costs);
    bool hasResources(std::vector<Resource> resources);
    bool isTileNeighbor(TilePiece *tile);
    void addResource(Resource newResource);
    void setAsWinner();
    bool haveWon();

    std::map<std::string, Resource> getTurnResources();
    std::vector<TilePiece*> getTerritory();
    std::vector<Resource> getResources();
    int getConstructionsNumber();
    sf::Color getColor();
    uint getId();

    void update(sf::Time dt);
private:
    uint empireId;
    std::vector<TilePiece*> territory;
    std::unordered_set<TilePiece*> neighbors;
    std::map<std::string, Resource> resources;
    std::map<std::string, Resource> turnResources;
    sf::Color color;
    int constructions;
    bool won;

    bool canPayResource(Resource resource);
    void addTileToTerritory(TilePiece *newTile);
    
    template<typename T>
    std::vector<T> mapToVector(const std::map<std::string, T>& inputMap); 
    
    class HumanResourceSource : public ResourceSource 
    {
    public:
        HumanResourceSource();
        Resource extract(sf::Time dt) override;
        Resource getEmptyResource() override { return HumanResource(0); }

        float consume(std::map<std::string, Resource>& resources, sf::Time dt);
        bool activate();

    private:
        bool isUpdated;
        float consumption;
        Resource foodResource;
    };

    HumanResourceSource hrSource;
};

#endif // EMPIRE_HPP
