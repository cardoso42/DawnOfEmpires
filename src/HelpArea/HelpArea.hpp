#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"
#include "HelpPage.hpp"

#include <SFML/Graphics.hpp>

class HelpArea : public sf::Drawable
{
public:
    HelpArea(sf::Vector2f viewSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
private:
    sf::RectangleShape background;
    std::vector<HelpPage*> pages;
    int currentPage = 0;
};

#endif // HELPAREA_HPP
