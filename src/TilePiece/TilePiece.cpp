#include "TilePiece.hpp"
#include "AssetManager.hpp"

TilePiece::TilePiece(float x, float y, int q, int r, sf::Color bgColor) 
    : tileId(IdGenerator::GenerateTileId()), q(q), r(r), bodyColor(bgColor),
    status(TilePiece::TileStatus::NONE), empireId(-1), decoration(nullptr)
{
#ifdef DEBUG
    text = new sf::Text(
        "(" + std::to_string(q) + ", " + std::to_string(r) + ")",
        AssetManager::GetFont("arial.ttf"), 12U
    );
    text->setFillColor(sf::Color::Black);
#endif

    body.setColor(bgColor);
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
    generateDecoration();
}

void TilePiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body);
    target.draw(border);

    if (decoration != nullptr)
    {
        target.draw(*decoration);
    }

#ifdef DEBUG
    target.draw(*text);
#endif
}

void TilePiece::setPosition(const sf::Vector2f& position)
{
    body.setPosition(position);
    border.setPosition(position);

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
    body.setColor(newColor);
}

void TilePiece::select()
{
    status |= TileStatus::SELECTED;
    border.setTexture(*AssetManager::GetTexture("hexagon-border-selected.png"));
}

void TilePiece::unselect()
{
    status &= (~TileStatus::SELECTED);
    body.setColor(bodyColor);
    border.setTexture(*AssetManager::GetTexture("hexagon-border.png"));
}

void TilePiece::annexTo(uint newOwner, sf::Color ownerColor)
{
    status = TilePiece::TileStatus::TERRITORY;
    bodyColor = ownerColor;
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
