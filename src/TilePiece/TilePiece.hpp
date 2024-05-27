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
    enum TileType { GRASS, FOREST, MINE, FARM, CONSTRUCTION, TYPES_NR_ITEMS };
    enum TileStatus { NONE, TERRITORY, MODIFIED, STATUS_NR_ITEMS };

    TilePiece();
    TilePiece(float x, float y, int q, int r, sf::Color bgColor = sf::Color::White);

    // Overrides
    void setPosition(const sf::Vector2f& position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void animate(sf::Time deltaTime);
    void paint(sf::Color color);
    void annexTo(uint newOwner, sf::Color newColor);
    void select();
    void unselect();

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
    sf::Color bodyColor;
    sf::Sprite border;
    sf::Sprite body;
#ifdef DEBUG
    sf::Text *text;
#endif
    
    TileStatus status;
    TileType type;
    uint tileId;

    int empireId;
    int q, r; // axial coordinates

    void generateDecoration();
};

#endif // TILE_PIECE_HPP
