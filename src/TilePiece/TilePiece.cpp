#include "TilePiece.hpp"
#include "ConstructionTile.hpp"
#include "TileTypeStrategyFactory.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"
#include "Resources.hpp"

TilePiece::TilePiece(float x, float y, int q, int r) 
    : tileId(IdGenerator::GenerateTileId()), ownerId(-1), decoration(nullptr),
        status(TilePiece::TileStatus::NONE), q(q), r(r), resourceSource(nullptr)
{
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

    TileTypeStrategyFactory factory;
    strategy = factory.createRandomStrategy();
    float amount = 5000 + rand() % 10000;
    float generation = .95 + rand() % 10 * 0.01;
    resourceSource = strategy->createResourceSource(amount, generation);
    paint(strategy->getColor());
}

bool TilePiece::improve()
{
    if (status &= TileStatus::MODIFIED)
    {
        return false;
    }

    status |= TileStatus::MODIFIED;

    generateDecoration();

    return true;
}

bool TilePiece::construct()
{
    if (!isConstructable())
    {
        return false;
    }

    status |= TileStatus::MODIFIED;
    strategy = new ConstructionTile();
    generateDecoration();

    return true;
}

Resource TilePiece::extractResource(sf::Time dt)
{
    if (status &= TileStatus::MODIFIED)
    {
        return resourceSource->extract(dt);
    }
    
    // TODO: criar exceções melhores
    throw std::logic_error("tile is not yet improved");
}

bool TilePiece::isOwnedBy(uint empireId)
{
    return empireId == ownerId;
}

bool TilePiece::isOwnedBySomeone()
{
    return ownerId != -1;
}

bool TilePiece::isImprovable()
{
    return ~status & TileStatus::MODIFIED;
}

bool TilePiece::isConstruction()
{
    return dynamic_cast<ConstructionTile*>(strategy) != nullptr;
}

bool TilePiece::isConstructable()
{
    for (auto resource : strategy->getConstructionCost())
    {
        if (resource.getName() == NullResource().getName())
        {
            return false;
        }
    }

    return isImprovable();
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
    if (decoration != nullptr)
    {
        delete decoration;
    }

    decoration = strategy->createDecoration();
    decoration->setPosition(body.getPosition());
    decoration->fitTo(getSize(), 0.6f);
}

void TilePiece::paint(sf::Color newColor)
{
    if (colorHistory.size() > 0 && newColor == colorHistory.back())
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

std::vector<Resource> TilePiece::getConstructionCost()
{
    return strategy->getConstructionCost();
}

std::vector<Resource> TilePiece::getImprovementCost()
{
    return strategy->getImprovementCost();
}

// Getters
std::vector<TilePiece*> TilePiece::getNeighbors() { return neighbors; }

sf::FloatRect TilePiece::getGlobalBounds() { return border.getGlobalBounds(); }

sf::Vector2i TilePiece::getSize() { return {107, 93}; }

int TilePiece::getId() const { return tileId; }

int TilePiece::getQ() const { return q; } 

int TilePiece::getR() const { return r; }
