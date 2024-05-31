#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"

#include <SFML/Graphics.hpp>

class HelpArea : public sf::Drawable
{
public:
    HelpArea(sf::Vector2f viewSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
private:
    sf::RectangleShape background;
    std::vector<sf::Text> texts;

    Empire* previousEmpire;
    TilePiece* previousTile;

    void createText(std::string newText, bool newSection = false);
};

#endif // HELPAREA_HPP
