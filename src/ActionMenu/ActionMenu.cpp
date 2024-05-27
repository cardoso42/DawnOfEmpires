#include "ActionMenu.hpp"
#include "ButtonCallback.hpp"
#include <iostream>
#include <cmath>

ActionMenu::ActionMenu(sf::Vector2f windowSize) : frame(windowSize)
{
    frame.setFillColor(sf::Color::White);
    frame.setOrigin(windowSize * 0.5f);
    frame.setPosition(windowSize * 0.5f);

    sf::Vector2f size = {windowSize.x * 0.6f, windowSize.y * 0.05f};
    buttons.push_back(ButtonMenu("Select initial tile", size, Callbacks::selectInitialTileBtnCb));
    buttons.push_back(ButtonMenu("Improve tile", size, Callbacks::improveTileBtnCb));
    organizeButtons();
}

void ActionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame);

    for (auto btn : buttons)
    {
        target.draw(btn);
    }
}

void ActionMenu::click(float x, float y)
{
    for (auto& btn : buttons)
    {
        btn.unselect();

        if (btn.getGlobalBounds().contains({x, y}))
        {
            btn.select();
        }
    }
}

void ActionMenu::organizeButtons()
{
    const int len = buttons.size();
    const float buttonHeight = buttons[0].getSize().y;
    const float frameHeight = frame.getSize().y;
    float interval = (frameHeight - len * buttonHeight) / (len + 1);
    interval = std::min(interval, 50.f);

    const float remainingSpace = frameHeight - len * (buttonHeight + interval + 1);
    if (remainingSpace < 0)
    {
        throw std::logic_error("o-oh! too crowd in here!");
    }

    float yDisplace = (remainingSpace + buttonHeight) / 2;
    for (int i = 0; i < len; i++)
    {
        buttons[i].setPosition({
            frame.getSize().x / 2, 
            yDisplace + (buttonHeight + interval) * i
        });
    }
}
