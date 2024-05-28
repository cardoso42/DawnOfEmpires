#include "ResourceBar.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"

ResourceBar::ResourceBar(sf::Vector2f size) :
    resourcesInfo("", AssetManager::GetFont("arial.ttf")), windowSize(size)
{
    resourcesInfo.setFillColor(sf::Color::Black);
}

void ResourceBar::update()
{
    Empire empire = *(GameContext::getPlayer());
    std::vector<Resource> empireResources = empire.getResources();
    std::string newText = "";

    for (auto resource : empireResources)
    {
        newText += resource.name + ": " + std::to_string(resource.amount) + "\t";
    }

    resourcesInfo.setString(newText);
    resourcesInfo.setOrigin(
        resourcesInfo.getLocalBounds().width * 0.5,
        resourcesInfo.getLocalBounds().height * 0.5f
    );
    resourcesInfo.setPosition(windowSize * 0.5f);
}

void ResourceBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(resourcesInfo);
}
