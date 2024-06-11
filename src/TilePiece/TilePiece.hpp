#ifndef TILE_PIECE_HPP
#define TILE_PIECE_HPP

#include "AssetManager.hpp"
#include "Animator.hpp"
#include "AnimatedAsset.hpp"
#include "IdGenerator.hpp"
#include "Resources.hpp"
#include "ResourceSource.hpp"
#include "TileTypeStrategy.hpp"

#include <SFML/Graphics.hpp>

class TilePiece : public sf::Drawable
{
public:
    enum TileStatus { NONE = 0x0, TERRITORY = 0x1, MODIFIED = 0x2, SELECTED = 0x4 };
    enum ConstructionType { MILITARY, CULTURE, ECONOMY };

    TilePiece(float x, float y, int q, int r);

    // Overrides
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setPosition(const sf::Vector2f& position);
    void animate(sf::Time deltaTime);
    void annexTo(uint newOwner, sf::Color newColor);
    bool improve();
    bool construct(ConstructionType type);
    void select();
    void unselect();

    Resource extractResource(sf::Time dt);

    bool isOwnedBy(uint empireId);
    bool isOwnedBySomeone();
    bool isModified();
    bool isImprovable();
    bool isConstruction();
    bool isConstructable();

    // getters
    std::string getTypeName();
    Resource getEmptyResource();
    std::vector<Resource> getConstructionCost();
    std::vector<Resource> getImprovementCost();
    std::vector<TilePiece*> getNeighbors();
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    int getId() const;
    int getQ() const;
    int getR() const;

    // setters
    int setNeighbors(std::vector<TilePiece*> newNeighbors);

    // Static
    static sf::Vector2i getSize();
private:
    ResourceSource *resourceSource;
    std::vector<TilePiece*> neighbors;
    AnimatedAsset *decoration;
    TileTypeStrategy* strategy;

    std::vector<sf::Color> colorHistory;
    sf::CircleShape ownerColor;
    sf::Sprite border;
    sf::Sprite body;
#ifdef DEBUG
    sf::Text *text;
#endif
    
    int status;
    uint tileId;
    int q, r; // axial coordinates
    int ownerId;

    void setStrategy(TileTypeStrategy* newStrategy);
    void generateRandomStrategy();
    void generateDecoration();
    void paint(sf::Color color);
};

#endif // TILE_PIECE_HPP
