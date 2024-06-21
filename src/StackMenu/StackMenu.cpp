#include "StackMenu.hpp"
#include <iostream>

StackMenu::StackMenu(GenericMenu *startingMenu) : BaseComponent()
{
    menus.push_back(startingMenu);
}

void StackMenu::addMenu(GenericMenu *menu)
{   
    menus.push_back(menu);
}

void StackMenu::goBack()
{
    menus.pop_back();
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
