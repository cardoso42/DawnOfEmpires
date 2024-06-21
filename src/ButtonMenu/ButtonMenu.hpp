#ifndef BUTTONMENU_HPP
#define BUTTONMENU_HPP

#include <SFML/Graphics.hpp>

#define CallbackFunction std::function<void(std::vector<void*>)>

class ButtonMenu : public sf::Drawable
{
public:
    ButtonMenu(std::string text, sf::Vector2f size);

    // Overrides
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void setCallback(CallbackFunction cb, std::vector<void*> parameters);
    void setSelectable(bool selectable);
    void setOutlineThickness(float thickness);
    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scale);

    sf::FloatRect getGlobalBounds();
    sf::Vector2f getSize();
    std::string getText();

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
    
};

#endif // BUTTONMENU_HPP
