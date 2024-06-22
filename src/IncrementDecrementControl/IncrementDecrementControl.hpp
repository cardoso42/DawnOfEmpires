#ifndef INCREMENTDECREMENTCONTROL_HPP
#define INCREMENTDECREMENTCONTROL_HPP

#include "BaseComponent.hpp"
#include <ButtonMenu.hpp>

class IncrementDecrementControl : public MenuElement
{
public:
    IncrementDecrementControl(sf::Vector2f size, std::string variableName, int* value, int minValue, int maxValue);

    void setPosition(sf::Vector2f pos) override;
    void setColor(sf::Color color) override;
    sf::FloatRect getGlobalBounds() override;
    sf::Color getColor() override;
    void select(float x, float y) override;
    void unselect() override;
    sf::Vector2f getSize() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update() override;

private:
    sf::RectangleShape frame;
    ButtonMenu fastIncrementButton;
    ButtonMenu incrementButton;
    ButtonMenu decrementButton;
    ButtonMenu fastDecrementButton;
    sf::Text valueText;

    int* value;
    int minValue;
    int maxValue;
};

#endif // INCREMENTDECREMENTCONTROL_HPP
