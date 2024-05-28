#include "ContextMenu.hpp"

#include <iostream>

ContextMenu::ContextMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    sf::Vector2f size = {windowSize.x * 0.8f, windowSize.y * 0.15f};
    buttons.push_back(ButtonMenu("btn1", size, [](std::vector<void*>) { std::cout << "btn1" << std::endl; }, {}));
    buttons.push_back(ButtonMenu("btn2", size, [](std::vector<void*>) { std::cout << "btn2" << std::endl; }, {}));

    organizeButtons();
}
