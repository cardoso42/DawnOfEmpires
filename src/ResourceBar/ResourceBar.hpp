#ifndef RESOURCEBAR_HPP
#define RESOURCEBAR_HPP

#include <SFML/Graphics.hpp>
#include <Empire.hpp>

class ResourceBar : public sf::Drawable
{
public:
    ResourceBar(sf::Vector2f size);

    void update();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Empire* empire;

    sf::Text resourcesInfo;
    sf::Vector2f windowSize;
    
    sf::RectangleShape wood;
    sf::RectangleShape minerals;
    sf::RectangleShape food;
};

#endif // RESOURCEBAR_HPP
