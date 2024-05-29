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
        HumanResourceSource()
            : ResourceSource(HumanResource(3), 0) {}

        Resource extract(sf::Time dt) override 
        {
            float realGeneration = generation * resource.getAmount() * dt.asSeconds();
            return Resource(resource.getName(), realGeneration, resource.getIcon());
        }

        bool activate()
        {
            if (this->generation == 0)
            {
                this->generation = 0.001;
                return true;
            }

            return false;
        }
    };

    HumanResourceSource hrSource;
};

#endif // EMPIRE_HPP
