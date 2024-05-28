#include "ActionMenu.hpp"
#include <iostream>

ActionMenu::ActionMenu(sf::Vector2f windowSize, Empire *currentEmpire, TilePiece *currentTile) : GenericMenu(windowSize)
{
    sf::Vector2f size = {windowSize.x * 0.6f, windowSize.y * 0.05f};

    std::vector<void*> parameters = {static_cast<void*>(currentEmpire), static_cast<void*>(currentTile)};

    buttons.push_back(ButtonMenu("Select initial tile", size, selectInitialTileBtnCb, parameters));
    buttons.push_back(ButtonMenu("Improve tile", size, improveTileBtnCb, {}));

    organizeButtons();
}

void ActionMenu::selectInitialTileBtnCb(std::vector<void*> parameters)
{
    Empire* empire = static_cast<Empire*>(parameters[0]);
    TilePiece* tile = static_cast<TilePiece*>(parameters[1]);

    empire->setStartingTerritory(tile);
}

void ActionMenu::improveTileBtnCb(std::vector<void*> parameters)
{

}
