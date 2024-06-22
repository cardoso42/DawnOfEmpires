#ifndef MENUELEMENT_HPP
#define MENUELEMENT_HPP

#include <SFML/Graphics.hpp>

class MenuElement : public sf::Drawable
{
public:
    MenuElement();
    virtual sf::Color getColor() = 0;
    virtual void setColor(sf::Color newColor) = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;
    virtual void select(float x, float y) = 0;
    virtual void unselect() = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;
    virtual sf::Vector2f getSize() = 0;
    virtual void update() = 0;
    virtual void updateText(std::string newText) = 0; // TODO: delete this
    virtual void setSelectable(bool selectable) = 0; // TODO: delete this
private:
};

#endif // MENUELEMENT_HPP
