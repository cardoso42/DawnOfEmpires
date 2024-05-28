#include "TilePiece.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"

TilePiece::TilePiece(float x, float y, int q, int r, sf::Color bgColor) 
    : tileId(IdGenerator::GenerateTileId()), q(q), r(r), colorHistory({bgColor}),
    status(TilePiece::TileStatus::NONE), ownerId(-1), decoration(nullptr)
{
#ifdef DEBUG
    text = new sf::Text(
        "(" + std::to_string(q) + ", " + std::to_string(r) + ")",
        AssetManager::GetFont("arial.ttf"), 12U
    );
    text->setFillColor(sf::Color::Black);
#endif

    body.setColor(bgColor);

    float radius = 5;
    ownerColor = sf::CircleShape(radius);
    ownerColor.setFillColor(sf::Color(0,0,0,0));
    ownerColor.setOrigin({radius / 2, radius / 2});

    setPosition({x, y});

    body.setTexture(*AssetManager::GetTexture("hexagon.png"));
    body.setOrigin(
        body.getTexture()->getSize().x * 0.5,
        body.getTexture()->getSize().y * 0.5
    );

    border.setTexture(*AssetManager::GetTexture("hexagon-border.png"));
    border.setOrigin(
        border.getTexture()->getSize().x * 0.5,
        border.getTexture()->getSize().y * 0.5
    );

    type = static_cast<TileType>(rand() % TileType::TYPES_NR_ITEMS);
    setColor();
}

void TilePiece::improve()
{
    if (type == TileType::FOREST || type == TileType::MINE)
    {
        generateDecoration();
    }
}

bool TilePiece::isOwnedBy(uint empireId)
{
    return empireId == ownerId;
}

void TilePiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body);
    target.draw(border);

    if (decoration != nullptr)
    {
        target.draw(*decoration);
    }

    if (ownerId != -1)
    {
        target.draw(ownerColor);
    }

#ifdef DEBUG
    target.draw(*text);
#endif
}

void TilePiece::setPosition(const sf::Vector2f& position)
{
    float deltaX = position.x - body.getPosition().x;
    float deltaY = position.y - body.getPosition().y;

    body.setPosition(position);
    border.setPosition(position);
    ownerColor.setPosition({position.x + getSize().x / 8, position.y - getSize().y / 3});

    if (decoration != nullptr)
    {
        decoration->setPosition(position);
    }

#ifdef DEBUG
    text->setPosition({position.x, position.y + 16});
#endif
}

sf::Vector2f TilePiece::getPosition() { return body.getPosition(); }

void TilePiece::animate(sf::Time deltaTime)
{
    if (decoration != nullptr)
    {
        decoration->animate(deltaTime);
    }
}

void TilePiece::setColor()
{
    switch (type)
    {
    case TileType::GRASS:
        paint(sf::Color(144,238,144));
        break;

    case TileType::FOREST:
        paint(sf::Color(34,139,34));
        break;

    case TileType::MINE:
        paint(sf::Color(211,211,211));
        break;

    case TileType::FARM:
    case TileType::CONSTRUCTION:
        paint(sf::Color(240,230,140));
        break;

    default:
        throw std::logic_error("generated value for tile type is invalid");
    }
}

void TilePiece::generateDecoration()
{
    switch (type)
    {
    case TileType::GRASS:
        decoration = new AnimatedAsset("grass.png");
        break;

    case TileType::FOREST:
        decoration = new AnimatedAsset("tree.png");
        break;

    case TileType::MINE:
        decoration = new AnimatedAsset("mine.png", 36, {120, 67});
        break;

    case TileType::FARM:
        decoration = new AnimatedAsset("barn.png");
        break;

    case TileType::CONSTRUCTION:
        decoration = new AnimatedAsset("pyramid.png");
        break;

    default:
        throw std::logic_error("generated value for tile type is invalid");
    }

    decoration->setPosition(body.getPosition());
    decoration->fitTo(getSize(), 0.6f);
}

void TilePiece::paint(sf::Color newColor)
{
    if (newColor == colorHistory.back())
    {
        return;
    }

    colorHistory.push_back(newColor);
    body.setColor(newColor);
}

void TilePiece::select()
{
    status |= TileStatus::SELECTED;
    GameContext::setTile(this);

    border.setTexture(*AssetManager::GetTexture("hexagon-border-selected.png"));
}

void TilePiece::unselect()
{
    GameContext::setTile(nullptr);
    status &= (~TileStatus::SELECTED);

    border.setTexture(*AssetManager::GetTexture("hexagon-border.png"));
}

void TilePiece::annexTo(uint newOwner, sf::Color newColor)
{
    status |= TilePiece::TileStatus::TERRITORY;
    ownerId = newOwner;
    ownerColor.setFillColor(newColor);
}

// Setters
int TilePiece::setNeighbors(std::vector<TilePiece*> newNeighbors)
{
    if (neighbors.size() > 0)
    {
        throw std::logic_error("Neighbors of tile " + std::to_string(tileId) + " already set");
    }

    neighbors = newNeighbors;

    return neighbors.size();
}

// Getters
std::vector<TilePiece*> TilePiece::getNeighbors() { return neighbors; }

sf::FloatRect TilePiece::getGlobalBounds() { return border.getGlobalBounds(); }

sf::Vector2i TilePiece::getSize() { return {107, 93}; }

int TilePiece::getId() const { return tileId; }

int TilePiece::getQ() const { return q; } 

int TilePiece::getR() const { return r; }
