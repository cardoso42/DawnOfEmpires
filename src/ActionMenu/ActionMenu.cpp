#include "ActionMenu.hpp"
#include <iostream>

ActionMenu::ActionMenu(sf::Vector2f windowSize)
{
    frame.setFillColor(sf::Color::Magenta);
    frame.setSize(windowSize);
    frame.setOrigin(windowSize * 0.5f);
    frame.setPosition(windowSize * 0.5f);
}

void ActionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame);
}
