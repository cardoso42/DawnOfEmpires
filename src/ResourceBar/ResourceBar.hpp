#ifndef RESOURCEBAR_HPP
#define RESOURCEBAR_HPP

#include <SFML/Graphics.hpp>
#include <Empire.hpp>

class ResourceBar : public sf::Drawable
{
public:
    ResourceBar(sf::Vector2f viewSize);

    void update();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    class ResourceBox : public sf::Drawable
    {
    public:
        ResourceBox(sf::Vector2f size, Resource resource);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void setPosition(sf::Vector2f pos);
    private:
        sf::RectangleShape frame;
        sf::RectangleShape body;
        sf::Text display;
    };
    Empire* empire;

    sf::Vector2f viewSize;
    
    std::vector<ResourceBox> resourceBoxes;
};

#endif // RESOURCEBAR_HPP
