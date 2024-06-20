#ifndef BASECOMPONENT_HPP
#define BASECOMPONENT_HPP

#include <SFML/Graphics.hpp>

class BaseComponent : public sf::Drawable
{
public:
    BaseComponent();
    virtual void update() = 0;
    virtual void click(float x, float y) = 0;
    virtual void animate(sf::Time deltaTime) = 0;
    virtual void handleKeyboardInput(sf::Keyboard::Key key) = 0;
private:
};

#endif // BASECOMPONENT_HPP
