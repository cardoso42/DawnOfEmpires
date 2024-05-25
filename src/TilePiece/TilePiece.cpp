#include "TilePiece.hpp"

TilePiece::TilePiece() : sf::Sprite(), decoration(nullptr), 
    tileId(IdGenerator::GenerateTileId())
{
    animator = new Animator(static_cast<sf::Sprite&>(*this));

    sf::Vector2i size = {200, 172};
    auto& animation = animator->CreateAnimation("NormalTile", "hexagon.png", sf::seconds(1), false);
    animation.AddFrames({0, 0}, size, 1);

    setOrigin({size.x * 0.5f, size.y * 0.5f});

    type = static_cast<TileType>(rand() % TileType::TYPES_NR_ITEMS);

    generateDecoration();
}

TilePiece::TilePiece(float x, float y) : TilePiece()
{
    setPosition({x, y});
}

void TilePiece::drawOn(sf::RenderWindow &window)
{
    window.draw(*this);

    if (decoration != nullptr)
    {
        window.draw(*decoration);
    }
}

void TilePiece::setPosition(const sf::Vector2f& position)
{
    sf::Sprite::setPosition(position);
 
    if (decoration != nullptr)
    {
        decoration->setPosition(position);
    }
}

void TilePiece::animate(sf::Time deltaTime)
{
    animator->Update(deltaTime);

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

    decoration->setOrigin({
        decoration->getTextureRect().width * 0.5f, 
        decoration->getTextureRect().height * 0.5f
    });
    decoration->setPosition(getPosition());
}
