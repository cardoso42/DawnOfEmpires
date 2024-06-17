#include "ResourceBar.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"

#include <sstream>
#include <iomanip>

ResourceBar::ResourceBar(sf::Vector2f viewSize) : viewSize(viewSize) { }

void ResourceBar::update()
{
    Empire empire = *(GameContext::getPlayer());
    std::vector<Resource> empireResources = empire.getResources();
    sf::Vector2f size;
    
    float interval = viewSize.x * 0.02f;
    float maxBoxWidth = viewSize.x * 0.2f;
    int maxNumberBoxes = static_cast<int>((viewSize.x - interval) / (interval + maxBoxWidth));

    if (empireResources.size() > maxNumberBoxes)
    {
        float actualBoxWidth = -interval + (viewSize.x - interval) / empireResources.size();
        size = {actualBoxWidth, viewSize.y * 0.9f};
    }
    else
    {
        interval = (viewSize.x - maxBoxWidth * empireResources.size()) / (empireResources.size() + 1);
        size = {maxBoxWidth, viewSize.y * 0.9f};
    }

    resourceBoxes.clear();
    for (int i = 0; i < empireResources.size(); i++)
    {
        ResourceBox newResourceBox(size, empireResources[i]);
        sf::Vector2f pos = {interval + i*(interval+size.x) + size.x * 0.5f, viewSize.y * 0.5f};
        newResourceBox.setPosition(pos);
        resourceBoxes.push_back(newResourceBox);
    }
}

void ResourceBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    auto bg = sf::RectangleShape(static_cast<sf::Vector2f>(target.getSize()));
    bg.setFillColor(sf::Color(180, 110, 60));

    target.draw(bg);
    for (auto box : resourceBoxes)
    {
        target.draw(box);
    }
}

// ResourceBox implementation
ResourceBar::ResourceBox::ResourceBox(sf::Vector2f size, Resource resource) 
    : frame(size), body(size - sf::Vector2f({10,10})), iconFrame(0),
    icon(*AssetManager::GetTexture(resource.getIcon()))
{
    frame.setFillColor(sf::Color(120, 50, 0));
    frame.setOrigin(frame.getSize() * 0.5f);

    body.setFillColor(sf::Color(139, 69, 19));
    body.setOrigin(body.getSize() * 0.5f);

    float originalSide = icon.getLocalBounds().height;
    float desiredSide = size.y * 0.5f;
    float scale = desiredSide / originalSide;

    icon.setOrigin(icon.getLocalBounds().width * 0.5f, icon.getLocalBounds().height * 0.5f);
    icon.setScale({scale, scale});

    if (icon.getLocalBounds().width > 0)
    {
        iconFrame = sf::CircleShape(icon.getLocalBounds().width * icon.getScale().x * 0.5f + 10);
        iconFrame.setFillColor(sf::Color(120, 50, 0));
        iconFrame.setOrigin(iconFrame.getRadius(), iconFrame.getRadius());
    }
    else
    {
        iconFrame = sf::CircleShape(0);
        iconFrame.setFillColor(sf::Color(120, 50, 0, 0));
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << resource.getAmount();
    std::string formattedAmount = stream.str();
    displayText = sf::Text(
        resource.getName() + "\n" + formattedAmount, 
        AssetManager::GetFont("anonymous.ttf"), 24
    );

    displayText.setOrigin(
        displayText.getLocalBounds().width * 0.5f,
        displayText.getLocalBounds().height * 0.5f
    );
}

void ResourceBar::ResourceBox::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    body.setPosition(pos);

    if (icon.getLocalBounds().width > 0)
    {
        displayText.setPosition({pos.x + icon.getLocalBounds().width * icon.getScale().x * 0.5f + 15, pos.y});
    }
    else
    {
        displayText.setPosition(pos);
    }

    float iconX = pos.x - frame.getSize().x * 0.5f + icon.getLocalBounds().width * icon.getScale().x * 0.5f + 25;
    float iconY = pos.y;

    iconFrame.setPosition(iconX, iconY);
    icon.setPosition(iconX, iconY);
}

void ResourceBar::ResourceBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(frame);
    target.draw(body);
    target.draw(displayText);
    target.draw(iconFrame);
    target.draw(icon);

// TODO: discover why the display text and its debug square doesn't match!
#ifdef DEBUG
    auto debug = sf::RectangleShape({displayText.getLocalBounds().width, displayText.getLocalBounds().height});
    debug.setFillColor(sf::Color(1,1,1,0));
    debug.setOutlineColor(sf::Color::Red);
    debug.setOutlineThickness(3);
    debug.setOrigin(debug.getSize() * 0.5f);
    debug.setPosition(displayText.getPosition());
    target.draw(debug);
#endif
}
