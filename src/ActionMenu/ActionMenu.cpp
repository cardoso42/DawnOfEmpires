#include "ActionMenu.hpp"
#include "ButtonCallback.hpp"
#include <iostream>
#include <cmath>

ActionMenu::ActionMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    sf::Vector2f size = {windowSize.x * 0.6f, windowSize.y * 0.05f};
    buttons.push_back(ButtonMenu("Select initial tile", size, Callbacks::selectInitialTileBtnCb));
    buttons.push_back(ButtonMenu("Improve tile", size, Callbacks::improveTileBtnCb));

    organizeButtons();
}
