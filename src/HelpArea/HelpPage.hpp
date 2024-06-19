#ifndef HELPPAGE_HPP
#define HELPPAGE_HPP

#include "SFML/Graphics.hpp"

class HelpPage : public sf::Drawable
{
public:
    HelpPage(sf::Vector2f windowSize);

    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
    sf::Vector2f size;
    std::vector<sf::Text> texts;
    sf::Text locator;

    void createText(std::string newText, int yDistance = 20);
    void resetTexts();
};

#endif // HELPPAGE_HPP
