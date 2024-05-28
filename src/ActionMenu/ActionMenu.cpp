#include "ActionMenu.hpp"
#include <iostream>
#include "GameContext.hpp"

ActionMenu::ActionMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    sf::Vector2f size = {windowSize.x * 0.6f, windowSize.y * 0.05f};

    // TODO: think about someway to hide and show new buttons throghout the game
    buttons.push_back(ButtonMenu("Select initial tile", size, selectInitialTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Improve tile", size, improveTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Annex tile", size, annexTileBtnCb, {}));

    organizeButtons();
}

void ActionMenu::annexTileBtnCb(std::vector<void *> parameters)
{
    Empire* empire = GameContext::getPlayer();
    TilePiece* tile = GameContext::getTile();

    if (empire == nullptr)
    {
        throw std::logic_error("At least one empire should be selected by now");
    }

    if (tile == nullptr)
    {
        std::cout << "You should select a tile first!" << std::endl;
        return;
    }

    if (tile->isOwnedBy(empire->getId()))
    {
        std::cout << "You already own this tile!" << std::endl;
        return;
    }

    if (tile->isOwnedBySomeone())
    {
        std::cout << "Don\'t be rude! Someone else already own this tile!" << std::endl;
        return;
    }

    empire->annexNewTile(tile);
}

void ActionMenu::selectInitialTileBtnCb(std::vector<void *> parameters)
{
    Empire* empire = GameContext::getPlayer();
    TilePiece* tile = GameContext::getTile();

    if (empire == nullptr)
    {
        throw std::logic_error("At least one empire should be selected by now");
    }

    if (tile == nullptr)
    {
        std::cout << "You should select a tile first!" << std::endl;
        return;
    }

    if (empire->getTerritory().size() > 0)
    {
        std::cout << "You already have a territory" << std::endl;
        return;
    }

    empire->setStartingTerritory(tile);
}

void ActionMenu::improveTileBtnCb(std::vector<void*> parameters)
{
    Empire* empire = GameContext::getPlayer();
    TilePiece* tile = GameContext::getTile();

    if (empire == nullptr)
    {
        throw std::logic_error("At least one empire should be selected by now");
    }
    
    if (tile == nullptr)
    {
        std::cout << "You should select a tile first!" << std::endl;
        return;
    }

    if (!tile->isOwnedBy(empire->getId()))
    {
        std::cout << "You can\'t improve not owned tiles!" << std::endl;
        return;
    }

    tile->improve();
}
