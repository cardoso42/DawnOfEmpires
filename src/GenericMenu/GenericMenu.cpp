#include "GenericMenu.hpp"
#include <iostream>

GenericMenu::GenericMenu(sf::Vector2f windowSize, sf::Color bgColor) : frame(windowSize)
{
    frame.setFillColor(bgColor);
    frame.setOrigin(windowSize * 0.5f);
    frame.setPosition(windowSize * 0.5f);
}

void GenericMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame);

    for (auto btn : buttons)
    {
        target.draw(btn);
    }
}

void GenericMenu::click(float x, float y)
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

void GenericMenu::organizeButtons()
{
    const int len = buttons.size();
    float buttonHeight = buttons[0].getSize().y;
    const float frameHeight = frame.getSize().y;

    float sumButtonHeights{0};
    for (auto& btn : buttons)
    {
        sumButtonHeights += btn.getSize().y;
    }

    float interval = (frameHeight - sumButtonHeights) / (len + 1);
    interval = std::min(interval, 50.f);

    const float remainingSpace = frameHeight - sumButtonHeights - len * (interval + 1);
    if (remainingSpace < 0)
    {
        throw std::logic_error("o-oh! too crowded in here!");
    }

    float previousBtnsHeight{0};
    for (int i = 0; i < len; i++)
    {
        buttonHeight = buttons[i].getSize().y;
        float yDisplace = (remainingSpace + buttonHeight) / 2;
        buttons[i].setPosition({
            frame.getSize().x / 2, 
            yDisplace + interval * i + previousBtnsHeight
        });

        previousBtnsHeight += buttons[i].getSize().y;
    }
}

