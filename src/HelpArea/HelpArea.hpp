#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include "TilePiece.hpp"

#include <SFML/Graphics.hpp>

class HelpArea : public sf::Drawable
{
public:
    HelpArea(sf::Vector2f viewSize);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    class TilePieceExample : public TilePiece
    {
    public:
        TilePieceExample(int x, int y, TileType type);
    };

    sf::Vector2f viewSize;
    sf::RectangleShape rect;
    TilePieceExample grassTile;
    TilePieceExample mineralTile;
    TilePieceExample forestTile;
    std::vector<sf::Text> texts;

};

#endif // HELPAREA_HPP
