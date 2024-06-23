#ifndef GENERICMENU_HPP
#define GENERICMENU_HPP

#include <SFML/Graphics.hpp>
#include <ButtonMenu.hpp>
#include <BaseComponent.hpp>
#include <IncrementDecrementControl.hpp>

class GenericMenu : public BaseComponent
{
public:
    GenericMenu(sf::Vector2f windowSize, sf::Color bgColor = sf::Color(255, 255, 255, 180));
    ~GenericMenu();

    void click(float x, float y) override;
    void animate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update() override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;
    void setButtonSize(sf::Vector2f size);
    void startNewColumn();
    virtual void setActions() { }; // To be controlled by the StackMenu class
    virtual std::string getName() { return "GenericMenu"; };

protected:
    std::vector<std::vector<MenuElement*>> buttons;
    sf::RectangleShape frame;
    sf::Vector2f buttonSize;
    int currentColumn;
    AnimatedAsset background;

    void addButton(ButtonMenu* button);
    void addButton(std::string msg, CallbackFunction callback, std::vector<void*> parameters);
    void addButton(std::string msg, sf::Vector2f size, CallbackFunction callback, std::vector<void*> parameters);
    void addIncDecControl(IncrementDecrementControl* control);
    void clearMenu();
    void organizeMenu();
    void organizeColumn(std::vector<MenuElement*>& column, float x);

    void setButtonTransparency(float alpha);
    const std::vector<std::string> bgImgs = {
        "cristo.png", "coliseu.png", "chichén-itzá.png", "great-wall.png", 
        "taj-mahal.png", "petra.png", "machu-pichu.png"};
    void setRandomBackground();
};

#endif // GENERICMENU_HPP
