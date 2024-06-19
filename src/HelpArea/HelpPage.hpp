#ifndef HELPPAGE_HPP
#define HELPPAGE_HPP

#include "SFML/Graphics.hpp"

class HelpPage : public sf::Drawable
{
public:
    HelpPage(sf::Vector2f windowSize);

    virtual void update() = 0;

protected:
    sf::Vector2f size;
};

#endif // HELPPAGE_HPP
