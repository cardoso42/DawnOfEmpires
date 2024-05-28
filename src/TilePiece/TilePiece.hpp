#ifndef TILE_PIECE_HPP
#define TILE_PIECE_HPP

#include "AssetManager.hpp"
#include "Animator.hpp"
#include "AnimatedAsset.hpp"
#include "IdGenerator.hpp"

#include <SFML/Graphics.hpp>

class TilePiece : public sf::Drawable
{
public:
    enum TileType { GRASS, FOREST, MINE, TYPES_NR_ITEMS, FARM, CONSTRUCTION };
    enum TileStatus { NONE = 0x0, TERRITORY = 0x1, MODIFIED = 0x2, SELECTED = 0x4 };

    TilePiece();
    TilePiece(float x, float y, int q, int r, sf::Color bgColor = sf::Color::White);

    // Overrides
    void setPosition(const sf::Vector2f& position);
    friend std::ostream& operator<<(std::ostream& os, const TilePiece& obj) {
        os << "(" << obj.q << ", " << obj.r << ")";
        return os;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void animate(sf::Time deltaTime);
    void paint(sf::Color color);
    void annexTo(uint newOwner, sf::Color newColor);
    void improve();
    void select();
    void unselect();

    bool isOwnedBy(uint empireId);

    // getters
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
    std::vector<TilePiece*> neighbors;
    AnimatedAsset *decoration;
    std::vector<sf::Color> colorHistory;
    sf::Sprite border;
    sf::Sprite body;
#ifdef DEBUG
    sf::Text *text;
#endif
    
    int status;
    TileType type;
    uint tileId;

    int ownerId;
    int q, r; // axial coordinates

    void generateDecoration();
    void setColor();
};

#endif // TILE_PIECE_HPP
