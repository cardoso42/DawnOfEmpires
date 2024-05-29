#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include <SFML/Graphics.hpp>

class HelpArea : public sf::Drawable
{
public:
    HelpArea(sf::Vector2f viewSize);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::Vector2f viewSize;
    sf::RectangleShape rect;
};

#endif // HELPAREA_HPP
