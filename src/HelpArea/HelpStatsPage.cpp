#include "HelpStatsPage.hpp"
#include <AssetManager.hpp>

HelpStatsPage::HelpStatsPage(sf::Vector2f windowSize) : HelpPage(windowSize)
{
    msg = sf::Text("Hello, World!", AssetManager::GetFont("anonymous.ttf"), 30);
    msg.setOrigin(msg.getLocalBounds().width * 0.5f, msg.getLocalBounds().height * 0.5f);
    msg.setPosition(windowSize * 0.5f);
    msg.setFillColor(sf::Color::White);
}

void HelpStatsPage::update()
{
}

void HelpStatsPage::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(msg);
}
