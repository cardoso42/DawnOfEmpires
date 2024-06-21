#include "ContextMenu.hpp"

#include <iostream>

ContextMenu::ContextMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    setButtonSize({windowSize.x * 0.8f, windowSize.y * 0.15f});

    addButton("btn1", [](std::vector<void*>) { std::cout << "btn1" << std::endl; }, {});
    addButton("btn2", [](std::vector<void*>) { std::cout << "btn2" << std::endl; }, {});

    organizeButtons();
}
