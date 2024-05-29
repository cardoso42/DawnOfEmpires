#include "HelpArea.hpp"

HelpArea::HelpArea(sf::Vector2f viewSize) : viewSize(viewSize), rect(viewSize)
{
    rect.setFillColor(sf::Color::Black);
    rect.setOrigin(rect.getSize() * 0.5f);
    rect.setPosition(viewSize * 0.5f);
}

void HelpArea::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);
}
