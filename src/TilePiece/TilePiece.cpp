#include "TilePiece.hpp"
#include "AssetManager.hpp"

TilePiece::TilePiece() : tileId(IdGenerator::GenerateTileId())
{
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

TilePiece::TilePiece(float x, float y, int q, int r, sf::Color bgColor) : TilePiece()
{
    this->q = q;
    this->r = r;

#ifdef DEBUG
    text = new sf::Text("(" + std::to_string(q) + ", " + std::to_string(r) + ")", AssetManager::GetFont("arial.ttf"), 12U);
    text->setFillColor(sf::Color::Black);
#endif

    body.setColor(bgColor);
    setPosition({x, y});
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
    border.setTexture(*AssetManager::GetTexture("hexagon-border-selected.png"));
}

void TilePiece::unselect()
{
    border.setTexture(*AssetManager::GetTexture("hexagon-border.png"));
}

// Getters
sf::FloatRect TilePiece::getGlobalBounds() { return border.getGlobalBounds(); }

sf::Vector2i TilePiece::getSize() { return {107, 93}; }

int TilePiece::getId() const { return tileId; }

int TilePiece::getQ() const { return q; } 

int TilePiece::getR() const { return r; }
