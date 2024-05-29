#include "ResourceBar.hpp"
#include "AssetManager.hpp"
#include "GameContext.hpp"

ResourceBar::ResourceBar(sf::Vector2f viewSize) : viewSize(viewSize) { }

void ResourceBar::update()
{
    Empire empire = *(GameContext::getPlayer());
    std::vector<Resource> empireResources = empire.getResources();
    sf::Vector2f size;
    
    float interval = viewSize.x * 0.1f;
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
    : frame(size), body(size - sf::Vector2f({10,10}))
{
    frame.setFillColor(sf::Color(120, 50, 0));
    frame.setOrigin(frame.getSize() * 0.5f);

    body.setFillColor(sf::Color(139, 69, 19));
    body.setOrigin(body.getSize() * 0.5f);

    display = sf::Text(
        resource.getName() + "\n" + std::to_string(resource.getAmount()), 
        AssetManager::GetFont("arial.ttf"), 24
    );

    display.setOrigin(
        display.getLocalBounds().width * 0.5f,
        display.getLocalBounds().height * 0.5f
    );
}

void ResourceBar::ResourceBox::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    body.setPosition(pos);
    display.setPosition(pos);
}

void ResourceBar::ResourceBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(frame);
    target.draw(body);
    target.draw(display);

// TODO: discover why the display text and its debug square doesn't match!
#ifdef DEBUG
    auto debug = sf::RectangleShape({display.getLocalBounds().width, display.getLocalBounds().height});
    debug.setFillColor(sf::Color(1,1,1,0));
    debug.setOutlineColor(sf::Color::Red);
    debug.setOutlineThickness(3);
    debug.setOrigin(debug.getSize() * 0.5f);
    debug.setPosition(display.getPosition());
    target.draw(debug);
#endif
}
