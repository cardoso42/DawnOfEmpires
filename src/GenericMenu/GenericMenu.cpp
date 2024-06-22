#include "GenericMenu.hpp"
#include <iostream>

GenericMenu::GenericMenu(sf::Vector2f windowSize, sf::Color bgColor) 
    : frame(windowSize), currentColumn(0), buttonSize({100, 10})
{
    buttons.push_back(std::vector<ButtonMenu>());

    frame.setFillColor(bgColor);
    frame.setOrigin(windowSize * 0.5f);
    frame.setPosition(windowSize * 0.5f);
}

void GenericMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame);

    for (auto btnColumn : buttons)
    {
        for (auto btn : btnColumn)
        {
            target.draw(btn);
        }
    }
}

void GenericMenu::update()
{
}

void GenericMenu::handleKeyboardInput(sf::Keyboard::Key key)
{
}

void GenericMenu::setButtonSize(sf::Vector2f size) { buttonSize = size; }

void GenericMenu::startNewColumn() 
{ 
    currentColumn++; 
    buttons.push_back(std::vector<ButtonMenu>());
}

void GenericMenu::click(float x, float y)
{
    for (auto& btnColumn : buttons)
    {
        for (auto& btn : btnColumn)
        {
            btn.unselect();
            if (btn.getGlobalBounds().contains({x, y}))
            {
                btn.select();
            }
        }
    }
}

void GenericMenu::animate(sf::Time deltaTime) { }

void GenericMenu::addButton(ButtonMenu button)
{
    buttons[currentColumn].push_back(button);
}

void GenericMenu::addButton(std::string msg, CallbackFunction callback, std::vector<void *> parameters)
{
    addButton(msg, buttonSize, callback, parameters);
}

void GenericMenu::addButton(
    std::string msg, sf::Vector2f size, CallbackFunction callback, std::vector<void *> parameters)
{
    auto button = ButtonMenu(msg, size);
    button.setCallback(callback, parameters);
    addButton(button);
}

void GenericMenu::clearButtons()
{
    for (auto& btnColumn : buttons)
    {
        btnColumn.clear();
    }
    buttons.clear();

    currentColumn = 0;
    buttons.push_back(std::vector<ButtonMenu>());
}

void GenericMenu::organizeButtons()
{
    float xDisplace = frame.getSize().x / (buttons.size() + 1);
    float x = xDisplace;

    for (auto& btnColumn : buttons)
    {
        organizeColumn(btnColumn, x);
        x += xDisplace;
    }
}

void GenericMenu::organizeColumn(std::vector<ButtonMenu> &column, float x)
{
    const int len = column.size();
    float buttonHeight = column[0].getSize().y;
    const float frameHeight = frame.getSize().y;

    float sumButtonHeights{0};
    for (auto& btn : column)
    {
        sumButtonHeights += btn.getSize().y;
    }

    float interval = (frameHeight - sumButtonHeights) / (len + 1);
    interval = std::min(interval, 50.f);

    const float remainingSpace = frameHeight - sumButtonHeights - len * (interval + 1);
    if (remainingSpace < 0)
    {
        throw std::logic_error("GenericMenu: o-oh! too crowded in here!");
    }

    float previousBtnsHeight{0};
    for (int i = 0; i < len; i++)
    {
        buttonHeight = column[i].getSize().y;
        float yDisplace = (remainingSpace + buttonHeight) / 2;
        column[i].setPosition({x, yDisplace + interval * i + previousBtnsHeight});

        previousBtnsHeight += column[i].getSize().y;
    }
}
