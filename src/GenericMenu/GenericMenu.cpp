#include "GenericMenu.hpp"
#include <iostream>

GenericMenu::GenericMenu(sf::Vector2f windowSize, sf::Color bgColor) 
    : frame(windowSize), currentColumn(0), buttonSize({100, 10})
{
    buttons.push_back(std::vector<MenuElement*>());

    frame.setFillColor(bgColor);
    frame.setOrigin(windowSize * 0.5f);
    frame.setPosition(windowSize * 0.5f);
}

GenericMenu::~GenericMenu()
{
    for (auto& btnColumn : buttons)
    {
        for (auto& btn : btnColumn)
        {
            delete btn;
        }
    }
}

void GenericMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame);

    for (auto btnColumn : buttons)
    {
        for (auto btn : btnColumn)
        {
            target.draw(*btn);
        }
    }
}

void GenericMenu::update()
{
    for (auto& btnColumn : buttons)
    {
        for (auto& btn : btnColumn)
        {
            btn->update();
        }
    }   
}

void GenericMenu::handleKeyboardInput(sf::Keyboard::Key key)
{
}

void GenericMenu::setButtonSize(sf::Vector2f size) { buttonSize = size; }

void GenericMenu::startNewColumn() 
{ 
    currentColumn++; 
    buttons.push_back(std::vector<MenuElement*>());
}

void GenericMenu::setButtonTransparency(float alpha)
{
    for (auto& btnColumn : buttons)
    {
        for (auto& btn : btnColumn)
        {
            auto currentColor = btn->getColor();
            currentColor.a = alpha;
            btn->setColor(currentColor);
        }
    }
}

void GenericMenu::click(float x, float y)
{
    for (auto& btnColumn : buttons)
    {
        for (auto& element : btnColumn)
        {
            element->unselect();
            if (element->getGlobalBounds().contains({x, y}))
            {
                element->select(x, y);
                return;
            }
        }
    }
}

void GenericMenu::animate(sf::Time deltaTime) { }

void GenericMenu::addButton(ButtonMenu* button)
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
    auto button = new ButtonMenu(msg, size);
    button->setCallback(callback, parameters);
    addButton(button);
}

void GenericMenu::addIncDecControl(IncrementDecrementControl* control)
{
    buttons[currentColumn].push_back(control);
}

void GenericMenu::clearMenu()
{
    for (auto& btnColumn : buttons)
    {
        btnColumn.clear();
    }
    buttons.clear();

    GameContext::clearAlphanumericKeyActions();

    currentColumn = 0;
    buttons.push_back(std::vector<MenuElement*>());
}

void GenericMenu::organizeMenu()
{
    float xDisplace = frame.getSize().x / (buttons.size() + 1);
    float x = xDisplace;

    for (auto& btnColumn : buttons)
    {
        organizeColumn(btnColumn, x);
        x += xDisplace;
    }
}

void GenericMenu::organizeColumn(std::vector<MenuElement*> &column, float x)
{
    const int len = column.size();
    const float frameHeight = frame.getSize().y;
    float buttonHeight = 0;

    float sumButtonHeights{0};
    for (auto& btn : column)
    {
        sumButtonHeights += btn->getGlobalBounds().height;
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
        buttonHeight = column[i]->getGlobalBounds().height;
        float yDisplace = (remainingSpace + buttonHeight) / 2;
        column[i]->setPosition({x, yDisplace + interval * i + previousBtnsHeight});

        previousBtnsHeight += column[i]->getGlobalBounds().height;
    }
}
