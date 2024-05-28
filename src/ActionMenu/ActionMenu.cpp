#include "ActionMenu.hpp"
#include <iostream>
#include "GameContext.hpp"

ActionMenu::ActionMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    sf::Vector2f size = {windowSize.x * 0.6f, windowSize.y * 0.05f};

    buttons.push_back(ButtonMenu("Select initial tile", size, selectInitialTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Improve tile", size, improveTileBtnCb, {}));

    organizeButtons();
}

void ActionMenu::selectInitialTileBtnCb(std::vector<void*> parameters)
{
    Empire* empire = GameContext::getPlayer();
    TilePiece* tile = GameContext::getTile();

    if (tile == nullptr || empire == nullptr)
    {
        return;
    }


    empire->setStartingTerritory(tile);
}

void ActionMenu::improveTileBtnCb(std::vector<void*> parameters)
{

}
