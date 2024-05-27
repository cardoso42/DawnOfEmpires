#ifndef GENERICMENU_HPP
#define GENERICMENU_HPP

#include <SFML/Graphics.hpp>
#include <ButtonMenu.hpp>

class GenericMenu : public sf::Drawable
{
public:
    GenericMenu(sf::Vector2f windowSize);

    void click(float x, float y);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    std::vector<ButtonMenu> buttons;
    sf::RectangleShape frame;
    void organizeButtons();

};

#endif // GENERICMENU_HPP
