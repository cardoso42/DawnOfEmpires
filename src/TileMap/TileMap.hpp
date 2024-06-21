#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "TilePiece.hpp"
#include "BaseComponent.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

struct hash_pair 
{
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const 
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);

        if (hash1 != hash2) 
        {
            return hash1 ^ hash2;              
        }
        
        return hash1;
    }
};

class TileMap : public BaseComponent
{
public:
    enum TileDirections { UP, DOWN, UP_RIGHT, DOWN_LEFT, UP_LEFT, DOWN_RIGHT };
    TileMap(int mapRadius, sf::Vector2f center);

    // Override
    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void animate(sf::Time deltaTime) override;
    void click(float x, float y) override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;

    TilePiece* getRandomTile();
    void selectTile(TilePiece* tile);

private:
    std::vector<TilePiece> tiles;
    std::unordered_map<std::pair<int, int>, int, hash_pair> tileMap;
    sf::Keyboard::Key lastVerticalDirectionKey;

    void selectNeighborTile(TileDirections direction);
    void generateHexMap(sf::Vector2f center, int mapRadius);
    TilePiece* getTile(uint id);
    std::vector<TilePiece*> getNeighbors(int q, int r);    
};

#endif // TILEMAP_HPP
