#include "TileMap.hpp"
#include "GameContext.hpp"

#include <cmath>

TileMap::TileMap(int mapRadius, sf::Vector2f center) : lastVerticalDirectionKey(sf::Keyboard::Up)
{
    generateHexMap(center, mapRadius);

    for (auto& tile : tiles)
    {
        tile.setNeighbors(getNeighbors(tile.getQ(), tile.getR()));
    }

    GameContext::addKeyAction(sf::Keyboard::Left, [this](std::vector<void*>) { handleKeyboardInput(sf::Keyboard::Left); });
    GameContext::addKeyAction(sf::Keyboard::Right, [this](std::vector<void*>) { handleKeyboardInput(sf::Keyboard::Right); });
    GameContext::addKeyAction(sf::Keyboard::Up, [this](std::vector<void*>) { handleKeyboardInput(sf::Keyboard::Up); });
    GameContext::addKeyAction(sf::Keyboard::Down, [this](std::vector<void*>) { handleKeyboardInput(sf::Keyboard::Down); });
}

TileMap::~TileMap()
{
    GameContext::clearDirectionalKeyActions();
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

void TileMap::update() 
{    
    for (auto& tile : tiles)
    {
        if (tile.isConstructable() || tile.isImprovable())
        {
            return;
        }
    }

    GameContext::notifyEvent(GameContext::GameEvents::GAME_OVER);
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
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

void TileMap::click(float x, float y)
{
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

void TileMap::handleKeyboardInput(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Left:
            if (lastVerticalDirectionKey == sf::Keyboard::Up)
            {
                selectNeighborTile(TileMap::TileDirections::UP_LEFT);
            }
            else if (lastVerticalDirectionKey == sf::Keyboard::Down) 
            {    
                selectNeighborTile(TileMap::TileDirections::DOWN_LEFT);
            }
            break;

        case sf::Keyboard::Right:
            if (lastVerticalDirectionKey == sf::Keyboard::Up) 
            {
                selectNeighborTile(TileMap::TileDirections::UP_RIGHT);
            } 
            else if (lastVerticalDirectionKey == sf::Keyboard::Down) 
            {
                selectNeighborTile(TileMap::TileDirections::DOWN_RIGHT);
            }
            break;

        case sf::Keyboard::Up:
            selectNeighborTile(TileMap::TileDirections::UP);
            lastVerticalDirectionKey = sf::Keyboard::Up;
            break;

        case sf::Keyboard::Down:
            selectNeighborTile(TileMap::TileDirections::DOWN);
            lastVerticalDirectionKey = sf::Keyboard::Down;
            break;

        default:
            break;
    }
}

void TileMap::selectNeighborTile(TileDirections direction)
{
    TilePiece* selected = GameContext::getTile();
    if (selected == nullptr)
    {
        return;
    }

    int q = selected->getQ();
    int r = selected->getR();

    switch (direction)
    {
        case UP:
            r -= 1;
            break;
        case DOWN:
            r += 1;
            break;
        case UP_RIGHT:
            q += 1;
            r -= 1;
            break;
        case DOWN_LEFT:
            q -= 1;
            r += 1;
            break;
        case UP_LEFT:
            q -= 1;
            break;
        case DOWN_RIGHT:
            q += 1;
            break;
    }

    auto it = tileMap.find(std::make_pair(q, r));
    if (it != tileMap.end())
    {
        selected->unselect();
        tiles[it->second].select();
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

void TileMap::selectTile(TilePiece* tileToSelect)
{
    auto selected = GameContext::getTile();
    if (selected != nullptr)
    {
        selected->unselect();
    }

    if (tileToSelect != nullptr)
    {
        tileToSelect->select();
    }
}
