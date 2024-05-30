#include "TilePiece.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"
#include <Resources.hpp>

TilePiece::TilePiece(float x, float y, int q, int r) 
    : tileId(IdGenerator::GenerateTileId()), q(q), r(r),
        status(TilePiece::TileStatus::NONE), ownerId(-1), decoration(nullptr),
        resourceSource(nullptr)
{
#ifdef DEBUG
    text = new sf::Text(
        "(" + std::to_string(q) + ", " + std::to_string(r) + ")",
        AssetManager::GetFont("anonymous.ttf"), 8U
    );
    text->setFillColor(sf::Color::Black);
#endif

    auto initialColor = sf::Color::White;
    colorHistory = std::vector<sf::Color>({initialColor});
    body.setColor(initialColor);

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

    float amount = 5000 + rand() % 10000;
    float generation = .95 + rand() % 10 * 0.01;

    switch (type)
    {
    case TileType::FOREST:
        resourceSource = new WoodResourceSource(amount, generation);
        break;
    
    case TileType::MINE:
        resourceSource = new MineralResourceSource(amount, generation);
        break;
    
    case TileType::GRASS:
        resourceSource = new FoodResourceSource(amount, generation);
        break;

    default:
        std::logic_error("Not possible to create a tile of type " + std::to_string(type));
        break;
    }

    setColor();
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
    type = TileType::CONSTRUCTION;
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
    return type == TileType::CONSTRUCTION;
}

bool TilePiece::isConstructable()
{
    return type == TileType::GRASS && isImprovable();
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
        paint(sf::Color(157,157,157));
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

std::vector<Resource> TilePiece::getConstructionCost()
{
    if (!isConstructable())
    {
        throw std::invalid_argument("Tile should be constructable for this function to be called");
    }

    return std::vector<Resource>({
        HumanResource(30),
        WoodResource(50),
        MineralResource(20)
    });
}

std::vector<Resource> TilePiece::getImprovementCost()
{
    std::vector<Resource> costs;

    // I just wanted to make sure that I know that it would be best if this was
    // a base class and each tile piece type extended it with its own data,
    // but to change this now would be time consuming and I prefer to focus
    // on other priorities.
    // TODO: change this class according to previous comment.
    switch (type)
    {
    case TileType::FOREST:
        costs.push_back(HumanResource(1));
        break;
    
    case TileType::MINE:
        costs.push_back(HumanResource(1));
        costs.push_back(WoodResource(30));
        break;
    
    case TileType::GRASS:
        costs.push_back(HumanResource(2));
        break;

    default:
        break;
    }

    return costs;
}

// Getters
std::vector<TilePiece*> TilePiece::getNeighbors() { return neighbors; }

sf::FloatRect TilePiece::getGlobalBounds() { return border.getGlobalBounds(); }

sf::Vector2i TilePiece::getSize() { return {107, 93}; }

int TilePiece::getId() const { return tileId; }

int TilePiece::getQ() const { return q; } 

int TilePiece::getR() const { return r; }
