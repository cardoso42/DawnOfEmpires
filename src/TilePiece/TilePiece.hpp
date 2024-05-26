#ifndef TILE_PIECE_HPP
#define TILE_PIECE_HPP

#include "AssetManager.hpp"
#include "Animator.hpp"
#include "AnimatedAsset.hpp"
#include "IdGenerator.hpp"

#include <SFML/Graphics.hpp>

class TilePiece : public sf::Sprite
{
public:
    enum TileType { GRASS, FOREST, MINE, FARM, CONSTRUCTION, TYPES_NR_ITEMS };

    TilePiece();
    TilePiece(float x, float y, sf::Color bgColor = sf::Color::White);

    // Overrides
    void setPosition(const sf::Vector2f& position);

    void animate(sf::Time deltaTime);
    void drawOn(sf::RenderWindow &window);
    void paint(sf::Color color);

    // Static
    static sf::Vector2i GetSize();
private:
    AnimatedAsset *decoration;
    Animator *animator;
    TileType type;
    uint tileId;

    void generateDecoration();
};

#endif // TILE_PIECE_HPP
