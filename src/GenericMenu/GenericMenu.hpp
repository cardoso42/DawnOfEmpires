#ifndef GENERICMENU_HPP
#define GENERICMENU_HPP

#include <SFML/Graphics.hpp>
#include <ButtonMenu.hpp>
#include <BaseComponent.hpp>

class GenericMenu : public BaseComponent
{
public:
    GenericMenu(sf::Vector2f windowSize, sf::Color bgColor = sf::Color::White);

    void click(float x, float y) override;
    void animate(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update() override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;
    void setButtonSize(sf::Vector2f size);
    void startNewColumn();
    virtual std::string getName() { return "GenericMenu"; };

protected:
    std::vector<std::vector<ButtonMenu>> buttons;
    sf::RectangleShape frame;
    sf::Vector2f buttonSize;
    int currentColumn;

    void addButton(ButtonMenu button);
    void addButton(std::string msg, CallbackFunction callback, std::vector<void*> parameters);
    void addButton(std::string msg, sf::Vector2f size, CallbackFunction callback, std::vector<void*> parameters);
    void clearButtons();
    void organizeButtons();
    void organizeColumn(std::vector<ButtonMenu>& column, float x);
};

#endif // GENERICMENU_HPP
