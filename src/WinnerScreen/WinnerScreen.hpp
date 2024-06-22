#ifndef WINNERSCREEN_HPP
#define WINNERSCREEN_HPP

#include "BaseComponent.hpp"
#include "ButtonMenu.hpp"
#include "Empire.hpp"

class WinnerScreen : public BaseComponent
{
public:
    WinnerScreen(sf::Vector2f windowSize, Empire winner);

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void animate(sf::Time deltaTime) override;
    void click(float x, float y) override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;

private:
    sf::Text winnerText;
    ButtonMenu goToMenuButton;
    ButtonMenu quitButton;
};

#endif // WINNERSCREEN_HPP
