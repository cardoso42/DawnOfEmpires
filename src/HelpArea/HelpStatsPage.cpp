#include "HelpStatsPage.hpp"
#include <AssetManager.hpp>
#include <GameContext.hpp>

HelpStatsPage::HelpStatsPage(sf::Vector2f windowSize) : HelpPage(windowSize) { }

void HelpStatsPage::update()
{
    resetTexts();
    
    auto empire = GameContext::getPlayer();
    auto tile = GameContext::getTile();

    // Show how many constructions they have
    // Show how many tiles they have
}

void HelpStatsPage::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    HelpPage::draw(target, states);
}
