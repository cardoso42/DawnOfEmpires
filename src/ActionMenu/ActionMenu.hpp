#ifndef ACTIONMENU_HPP
#define ACTIONMENU_HPP

#include "SFML/Graphics.hpp"
#include <ButtonMenu.hpp>

class ActionMenu : public sf::Drawable
{
public:
    ActionMenu(sf::Vector2f windowSize);

    void click(float x, float y);

    // Override
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::RectangleShape frame;
    std::vector<ButtonMenu> buttons;

    void organizeButtons();
};

#endif // ACTIONMENU_HPP
