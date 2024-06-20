#ifndef RESOURCEBAR_HPP
#define RESOURCEBAR_HPP

#include <SFML/Graphics.hpp>
#include <Empire.hpp>
#include "BaseComponent.hpp"

class ResourceBar : public BaseComponent
{
public:
    ResourceBar(sf::Vector2f viewSize);

    void update() override;
    void click(float x, float y) override;
    void animate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;

private:
    class ResourceBox : public sf::Drawable
    {
    public:
        ResourceBox(sf::Vector2f size, Resource resource, float resourceVariation);
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void setPosition(sf::Vector2f pos);
    private:
        sf::RectangleShape frame;
        sf::RectangleShape body;
        sf::CircleShape iconFrame;
        sf::Text displayText;
        sf::Text amountVariation;
        sf::Sprite icon;

#ifdef DEBUG
        sf::RectangleShape displayDebug, iconDebug, amountDebug;
        sf::RectangleShape createDebugSquare(sf::FloatRect bounds, sf::Vector2f pos);
#endif
    };
    Empire* empire;

    sf::Vector2f viewSize;
    
    std::vector<ResourceBox> resourceBoxes;
};

#endif // RESOURCEBAR_HPP
