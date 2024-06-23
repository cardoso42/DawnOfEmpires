#include "TilePiece.hpp"
#include "TileTypeStrategyFactory.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"
#include "Resources.hpp"

TilePiece::TilePiece(float x, float y, int q, int r)
    : tileId(IdGenerator::GenerateTileId()), ownerId(-1), decoration(nullptr),
        strategy(nullptr), status(TileStatus::NONE), resourceSource(nullptr),
        q(q), r(r)
{
#ifdef DEBUG
    text = new sf::Text(
        "(" + std::to_string(tileId) + ")",
        AssetManager::GetFont("anonymous.ttf"), 8U
    );
    text->setFillColor(sf::Color::Black);
#endif

    float radius = 5;
    ownerColor = sf::CircleShape(radius);
    ownerColor.setFillColor(sf::Color(0,0,0,0));
    ownerColor.setOrigin({radius / 2, radius / 2});
    ownerColor.setOutlineColor(sf::Color::Black);
    ownerColor.setOutlineThickness(1);

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
    setStrategy(factory.createRandomStrategy());
}

bool TilePiece::improve()
{
    if (!isImprovable())
    {
        return false;
    }

    status |= TileStatus::MODIFIED;

    GameContext::playSound(strategy->getSoundBuffer());
    generateDecoration();

    return true;
}

bool TilePiece::construct(ConstructionType type)
{
    if (!isConstructable())
    {
        return false;
    }

    status |= TileStatus::MODIFIED;

    switch (type)
    {
    case ConstructionType::ECONOMY:
        setStrategy(new EconomyConstructionTile());
        break;
    
    case ConstructionType::CULTURE:
        setStrategy(new CultureConstructionTile());
        break;
    
    case ConstructionType::MILITARY:
        setStrategy(new MilitaryConstructionTile());
        break;

    default:
        break;
    }

    GameContext::playSound(strategy->getSoundBuffer());
    generateDecoration();

    return true;
}

Resource TilePiece::extractResource(sf::Time dt)
{
    if (isModified() && resourceSource != nullptr && (~status & TileStatus::DIED))
    {
        if (resourceSource->canExtract())
        {
            auto extractedResource = resourceSource->extract(dt);
            return extractedResource;
        }
        else
        {
            status |= TileStatus::DIED;
            generateDecoration();
        }
    }
    
    return NullResource();
}

bool TilePiece::isOwnedBy(uint empireId)
{
    return empireId == ownerId;
}

bool TilePiece::isOwnedBySomeone()
{
    return ownerId != -1;
}

bool TilePiece::isModified()
{
    return status & TileStatus::MODIFIED;
}

bool TilePiece::isImprovable()
{
    for (auto resource : strategy->getImprovementCost())
    {
        if (resource.getName() == NullResource().getName())
        {
            return false;
        }
    } 

    return ~status & TileStatus::MODIFIED;
}

bool TilePiece::isConstruction()
{
    return dynamic_cast<ConstructionTile*>(strategy);
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

void TilePiece::setStrategy(TileTypeStrategy* newStrategy)
{    
    if (newStrategy == nullptr)
    {
        return;
    }

    if (strategy != nullptr)
    {
        delete strategy;
    }

    strategy = newStrategy;
    
    resourceSource = strategy->createResourceSource();

    paint(strategy->getColor());
}

void TilePiece::generateDecoration()
{
    if (decoration != nullptr)
    {
        delete decoration;
    }

    if (resourceSource->canExtract())
    {
        decoration = strategy->createDecoration();
    }
    else
    {
        paint(sf::Color::Red);
        decoration = strategy->createEmptyDecoration();
    }

    if (decoration != nullptr)
    {
        decoration->setPosition(body.getPosition());
        decoration->fitTo(getSize(), 0.7f);
    }
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

void TilePiece::addBonus(float bonus)
{
    resourceSource->addBonus(bonus);
}

void TilePiece::annexTo(uint newOwner, sf::Color newColor)
{
    status |= TilePiece::TileStatus::TERRITORY;

    if (ownerId != -1)
    {
        GameContext::stealLand(this);
    }

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

std::string TilePiece::getTypeName()
{
    return strategy->getName();
}

Resource TilePiece::getEmptyResource()
{
    if (!isModified())
    {
        return NullResource();
    }

    return resourceSource->getEmptyResource();
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
