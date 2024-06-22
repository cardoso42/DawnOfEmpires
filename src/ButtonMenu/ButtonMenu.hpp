#ifndef BUTTONMENU_HPP
#define BUTTONMENU_HPP

#include <SFML/Graphics.hpp>
#include <GameContext.hpp>
#include <MenuElement.hpp>

class ButtonMenu : public MenuElement
{
public:
    ButtonMenu(std::string text, sf::Vector2f size, bool visible = true);

    // Overrides
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPosition(sf::Vector2f pos) override;
    void setColor(sf::Color color) override;
    sf::FloatRect getGlobalBounds() override;
    sf::Color getColor() override;
    void select(float x, float y) override;
    void unselect() override;
    sf::Vector2f getSize() override;
    void updateText(std::string newText) override;
    void setSelectable(bool selectable) override;
    void update() override;
    
    void setCallback(CallbackFunction cb, std::vector<void*> parameters);
    void setOutlineThickness(float thickness);
    void setScale(sf::Vector2f scale);

    std::string getText();


private:
    sf::RectangleShape frame;
    sf::Text btnText;
    CallbackFunction btnCb;
    std::vector<void*> cbParameters;
    bool selectable;
    bool isSelected;
    bool isVisible;
    
};

#endif // BUTTONMENU_HPP
