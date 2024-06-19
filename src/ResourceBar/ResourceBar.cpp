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
    std::map<std::string, Resource> turnResources = empire.getTurnResources();
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
        ResourceBox newResourceBox(size, empireResources[i], turnResources[empireResources[i].getName()].getAmount());
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
ResourceBar::ResourceBox::ResourceBox(sf::Vector2f size, Resource resource, float resourceVariation) 
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

    std::stringstream variationStream;
    variationStream << std::fixed << std::setprecision(1) << resourceVariation;
    amountVariation = sf::Text(variationStream.str(), AssetManager::GetFont("anonymous.ttf"), 24);
    if (resourceVariation > 0)
    {
        amountVariation.setFillColor(sf::Color::Green);
    }
    else if (resourceVariation < 0)
    {
        amountVariation.setFillColor(sf::Color::Red);
    }
    else
    {
        amountVariation.setFillColor(sf::Color::White);
    }
    amountVariation.setOrigin(0, amountVariation.getLocalBounds().height * 0.5f);
}

void ResourceBar::ResourceBox::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    body.setPosition(pos);

    // *** {icon} *** {displayText} *** {amountVariation} ***
    // or, if there is no available icon:
    // *** {displayText} *** {amountVariation} ***
    // *** = equal sized intervals

    float frameWidth = frame.getSize().x;
    float iconWidth = iconFrame.getGlobalBounds().width;
    float displayTextWidth = displayText.getGlobalBounds().width;
    float variationTextWidth = amountVariation.getGlobalBounds().width;
    float freeSpace = frameWidth - iconWidth - displayTextWidth - variationTextWidth;
    float interval = freeSpace / 4;

    if (freeSpace < 0)
    {
        throw std::logic_error("o-oh! too crowded in here");
    }

    float iconX = pos.x - frameWidth * 0.5f + iconWidth * 0.5f + interval;
    iconFrame.setPosition(iconX, pos.y);
    icon.setPosition(iconX, pos.y);

    float displayTextX;
    if (icon.getLocalBounds().width > 0)
    {
        displayTextX = iconX + (iconWidth + displayTextWidth) * 0.5f + interval;
    }
    else
    {
        interval = freeSpace / 3;
        displayTextX = pos.x - frameWidth * 0.5f + displayTextWidth * 0.5f + interval;
    }
    displayText.setPosition(displayTextX, pos.y);

    float amountX = displayTextX + (displayTextWidth + variationTextWidth) * 0.5f + interval;
    amountVariation.setPosition(amountX, pos.y);

#ifdef DEBUG
    displayDebug = createDebugSquare(displayText.getGlobalBounds(), displayText.getPosition());
    iconDebug = createDebugSquare(iconFrame.getGlobalBounds(), iconFrame.getPosition());
    amountDebug = createDebugSquare(amountVariation.getGlobalBounds(), amountVariation.getPosition());
#endif
}

void ResourceBar::ResourceBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(frame);
    target.draw(body);
    target.draw(displayText);
    target.draw(amountVariation);
    target.draw(iconFrame);
    target.draw(icon);

#ifdef DEBUG
// TODO: discover why the display text and its debug square doesn't match!
    target.draw(displayDebug);
    target.draw(iconDebug);
    target.draw(amountDebug);
#endif
}

#ifdef DEBUG
sf::RectangleShape ResourceBar::ResourceBox::createDebugSquare(sf::FloatRect bounds, sf::Vector2f pos)
{
    auto debug = sf::RectangleShape({bounds.width, bounds.height});
    debug.setFillColor(sf::Color(1,1,1,0));
    debug.setOutlineColor(sf::Color::Red);
    debug.setOutlineThickness(3);
    debug.setOrigin(debug.getSize() * 0.5f);
    debug.setPosition(pos);
    return debug;
}
#endif
