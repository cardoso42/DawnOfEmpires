#include "TileMap.hpp"
#include "GameContext.hpp"

#include <cmath>

TileMap::TileMap(int mapRadius, sf::Vector2f center)
{
    generateHexMap(center, mapRadius);

    for (auto& tile : tiles)
    {
        tile.setNeighbors(getNeighbors(tile.getQ(), tile.getR()));
    }
}

void TileMap::generateHexMap(sf::Vector2f center, int mapRadius) 
{
    sf::Vector2i tileSize = TilePiece::getSize();
    float hexWidth = tileSize.x;
    float hexRadius = hexWidth / 2.0f;
    float hexHeight = std::sqrt(3.0f) * hexRadius;

    for (int q = -mapRadius; q <= mapRadius; ++q) 
    {
        int r1 = std::max(-mapRadius, -q - mapRadius);
        int r2 = std::min(mapRadius, -q + mapRadius);

        for (int r = r1; r <= r2; ++r) 
        {
            float x = hexWidth * (q * 3.0f / 4.0f);
            float y = hexHeight * (r + q / 2.0f);
            tiles.push_back(TilePiece(x + center.x, y + center.y, q, r));
            tileMap[std::make_pair(q, r)] = tiles.size() - 1;
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& tile : tiles)
    {
        target.draw(tile);
    }
}

void TileMap::animate(sf::Time deltaTime)
{
    for (auto& tile : tiles)
    {
        tile.animate(deltaTime);
    }
}

void TileMap::click(int x, int y)
{
    // TODO: problema ao clicar porque como o globalBounds retorna um 
    // retângulo, não coincide exatamente com os hexagonos, fazendo com que ao 
    // clicar no canto de alguns hex, selecione o vizinho na verdade
    TilePiece* selected = GameContext::getTile();

    bool clickedOnTile{false};
    for (auto& tile : tiles)
    {
        if (tile.getGlobalBounds().contains(sf::Vector2f(x, y)))
        {
            clickedOnTile = true;

            if (selected == nullptr)
            {
                tile.select();
            }
            else if (tile.getId() != selected->getId())
            {
                selected->unselect();
                tile.select();
            }
            else
            {
                tile.unselect();
            }
            break;
        }
    }

    if (!clickedOnTile && selected != nullptr)
    {
        selected->unselect();
    }
}

TilePiece* TileMap::getTile(uint id)
{
    for (auto& tile : tiles)
    {
        if (tile.getId() == id)
        {
            return &tile;
        }
    }

    return nullptr;
}

std::vector<TilePiece*> TileMap::getNeighbors(int q, int r)
{
    std::vector<TilePiece*> neighbors;
    std::vector<std::pair<int, int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, -1}, {-1, 1}
    };

    for (const auto& dir : directions) 
    {
        int neighborQ = q + dir.first;
        int neighborR = r + dir.second;
        
        auto it = tileMap.find(std::make_pair(neighborQ, neighborR));
        if (it != tileMap.end()) 
        {
            neighbors.push_back(&tiles[it->second]);
        }
    }

    return neighbors;
}

TilePiece* TileMap::getRandomTile()
{
    srand(time(NULL));
    int i = rand() % tiles.size();
    return &tiles[i];
}
