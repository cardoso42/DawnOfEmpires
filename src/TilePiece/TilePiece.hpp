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

    TilePiece();
    TilePiece(float x, float y, sf::Color bgColor = sf::Color::White);

    // Overrides
    void setPosition(const sf::Vector2f& position);
    sf::FloatRect getGlobalBounds();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void animate(sf::Time deltaTime);
    void paint(sf::Color color);
    void select();
    void unselect();

    // Static
    static sf::Vector2i GetSize();
private:
    sf::Sprite border;
    sf::Sprite body;
    
    AnimatedAsset *decoration;
    
    TileType type;
    uint tileId;

    void generateDecoration();
};

#endif // TILE_PIECE_HPP
