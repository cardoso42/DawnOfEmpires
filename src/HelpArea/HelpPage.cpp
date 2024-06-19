#include "HelpPage.hpp"
#include <AssetManager.hpp>

HelpPage::HelpPage(sf::Vector2f windowSize) : size(windowSize) 
{
    locator = sf::Text("", AssetManager::GetFont("anonymous.ttf"));
    locator.setPosition({10, 0});
    texts.push_back(locator);
}

void HelpPage::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto& text : texts)
    {
        target.draw(text);
    }
}

void HelpPage::createText(std::string newText, int yDistance)
{
    sf::Text text(newText, AssetManager::GetFont("anonymous.ttf"), 20);
    text.setPosition(texts.back().getPosition().x, texts.back().getPosition().y + yDistance);
    texts.push_back(text);
}

void HelpPage::resetTexts()
{
    texts.clear();
    texts.push_back(locator);
}
