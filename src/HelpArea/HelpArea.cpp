#include "HelpArea.hpp"

#include "GameContext.hpp"
#include "HelpActionsPage.hpp"

HelpArea::HelpArea(sf::Vector2f viewSize) : background(viewSize)
{
    background.setFillColor(sf::Color(0, 0, 0, 200));

    pages.push_back(new HelpActionsPage(viewSize, background.getPosition()));

    currentPage = 0;
}

void HelpArea::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(*pages[currentPage], states);
}

void HelpArea::update()
{
    pages[currentPage]->update();
}
