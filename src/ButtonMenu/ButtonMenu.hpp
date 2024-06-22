#ifndef BUTTONMENU_HPP
#define BUTTONMENU_HPP

#include <SFML/Graphics.hpp>
#include <GameContext.hpp>
#include <BaseComponent.hpp>

class ButtonMenu : public BaseComponent
{
public:
    ButtonMenu(std::string text, sf::Vector2f size, bool visible = true);

    // Overrides
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void click(float x, float y) override;
    void animate(sf::Time deltaTime) override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;
    void update() override;
    
    void setCallback(CallbackFunction cb, std::vector<void*> parameters);
    void setSelectable(bool selectable);
    void setOutlineThickness(float thickness);
    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scale);
    void setColor(sf::Color color);

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getSize();
    std::string getText();
    sf::Color getColor();

    void select();
    void unselect();
    void updateText(std::string newText);

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
