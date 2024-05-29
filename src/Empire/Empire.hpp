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
            : ResourceSource(HumanResource(0), 0), foodResource(FoodResource(0)) {}

        Resource extract(sf::Time dt) override 
        {
            if (!isUpdated)
            {
                throw std::logic_error("To call extract on HumanResourceSource you should first call consume");
            }
            isUpdated = false;

            float realGeneration = generation * foodResource.getAmount() * dt.asSeconds();
            
            resource += realGeneration;
            
            return Resource(resource.getName(), realGeneration, resource.getIcon());
        }

        void consume(std::map<std::string, Resource>& resources, sf::Time dt)
        {
            if (resources.find("Food") == resources.end())
            {
                foodResource = FoodResource(0);
            }
            else
            {
                resources["Food"] -= consumption * dt.asSeconds();
                foodResource = resources["Food"];
            }

            isUpdated = true;
        }

        bool activate()
        {
            if (this->generation == 0)
            {
                this->generation = 0.001;
                this->consumption = 0.1;
                return true;
            }

            return false;
        }

    private:
        bool isUpdated{false};
        float consumption{0};

        Resource foodResource;
    };

    HumanResourceSource hrSource;
};

#endif // EMPIRE_HPP
