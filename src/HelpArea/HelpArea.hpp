#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"
#include "HelpPage.hpp"

#include <SFML/Graphics.hpp>

// TODO: Add something to tell the user that he can change the page on the help area

class HelpArea : public sf::Drawable
{
public:
    HelpArea(sf::Vector2f viewSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
    void click();

private:
    sf::RectangleShape background;
    std::vector<HelpPage*> pages;
    int currentPage = 0;
};

#endif // HELPAREA_HPP
