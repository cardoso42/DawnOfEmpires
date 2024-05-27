#ifndef ACTIONMENU_HPP
#define ACTIONMENU_HPP

#include "SFML/Graphics.hpp"

class ActionMenu : public sf::Drawable
{
public:
    ActionMenu(sf::Vector2f windowSize);

    void click(int x, int y);

    // Override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::RectangleShape frame;
};

#endif // ACTIONMENU_HPP
