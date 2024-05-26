#include "TilePiece.hpp"

TilePiece::TilePiece() : sf::Sprite(), tileId(IdGenerator::GenerateTileId())
{
    animator = new Animator(static_cast<sf::Sprite&>(*this));

    auto& animation = animator->CreateAnimation("NormalTile", "hexagon.png", sf::seconds(1), false);
    animation.AddFrames({0, 0}, GetSize(), 1);

    setOrigin({GetSize().x * 0.5f, GetSize().y * 0.5f});

    type = static_cast<TileType>(rand() % TileType::TYPES_NR_ITEMS);

    generateDecoration();
}

TilePiece::TilePiece(float x, float y, sf::Color bgColor) : TilePiece()
{
    setColor(bgColor);
    setPosition({x, y});
}

void TilePiece::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(static_cast<sf::Sprite>(*this));

    if (decoration != nullptr)
    {
        target.draw(*decoration);
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

    decoration->setPosition(getPosition());
    decoration->fitTo(GetSize(), 0.6f);
}

sf::Vector2i TilePiece::GetSize()
{
    return {107, 93};
}

void TilePiece::paint(sf::Color newColor)
{
    setColor(newColor);
}
