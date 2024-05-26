#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "TilePiece.hpp"

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

class TileMap : public sf::Drawable
{
public:
    TileMap(int mapRadius, sf::Vector2f center);

    // Override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void animate(sf::Time deltaTime);
    void click(int x, int y);

private:
    std::vector<TilePiece> tiles;
    std::unordered_map<std::pair<int, int>, int, hash_pair> tileMap;
    uint selectedTileId;

    void generateHexMap(sf::Vector2f center, int mapRadius);
    TilePiece* getTile(uint id);
    std::vector<TilePiece*> getNeighbors(int q, int r);    
};

#endif // TILEMAP_HPP
