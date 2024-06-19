#include "HelpArea.hpp"

#include "GameContext.hpp"
#include "HelpActionsPage.hpp"
#include "HelpStatsPage.hpp"

HelpArea::HelpArea(sf::Vector2f viewSize) : background(viewSize)
{
    background.setFillColor(sf::Color(0, 0, 0, 200));

    pages.push_back(new HelpActionsPage(viewSize));
    pages.push_back(new HelpStatsPage(viewSize));

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

void HelpArea::click()
{
    currentPage = (++currentPage) % pages.size();
}
