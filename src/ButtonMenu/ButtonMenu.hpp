#ifndef BUTTONMENU_HPP
#define BUTTONMENU_HPP

#include <SFML/Graphics.hpp>

class ButtonMenu : public sf::Drawable
{
public:
    ButtonMenu(std::string text, sf::Vector2f size, std::function<void()> cb);

    // Overrides
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setPosition(sf::Vector2f pos);
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getSize();

    void select();
    void unselect();
private:
    sf::RectangleShape frame;
    sf::Text btnText;
    std::function<void()> btnCb;
};

#endif // BUTTONMENU_HPP
