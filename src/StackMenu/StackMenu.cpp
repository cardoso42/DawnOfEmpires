#include "StackMenu.hpp"
#include <iostream>

StackMenu::StackMenu(GenericMenu *startingMenu) : BaseComponent()
{
    addMenu(startingMenu);
}

StackMenu::~StackMenu()
{
    for (auto menu : menus)
    {
        delete menu;
    }

    menus.clear();
}

void StackMenu::addMenu(GenericMenu *menu)
{   
    menus.push_back(menu);
    menu->setActions();
}

void StackMenu::goBack()
{
    if (menus.size() == 1)
    {
        return;
    }

    delete menus.back();
    menus.pop_back();
    menus.back()->setActions();
}

void StackMenu::update()
{
    menus.back()->update();
}

void StackMenu::animate(sf::Time deltaTime)
{
    menus.back()->animate(deltaTime);
}

void StackMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*menus.back());
}

void StackMenu::handleKeyboardInput(sf::Keyboard::Key key)
{
    menus.back()->handleKeyboardInput(key);
}

void StackMenu::click(float x, float y)
{
    menus.back()->click(x, y);
}

GenericMenu *StackMenu::getCurrentMenu()
{
    return menus.back();
}
