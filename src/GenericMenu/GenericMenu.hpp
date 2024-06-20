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

protected:
    std::vector<ButtonMenu> buttons;
    sf::RectangleShape frame;
    void organizeButtons();

};

#endif // GENERICMENU_HPP
