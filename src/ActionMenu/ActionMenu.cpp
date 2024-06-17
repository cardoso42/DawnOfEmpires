#include "ActionMenu.hpp"
#include <iostream>
#include "GameContext.hpp"

ActionMenu* ActionMenu::instance = nullptr;

ActionMenu::ActionMenu(sf::Vector2f windowSize) : 
    GenericMenu(windowSize, sf::Color(191, 191, 191)),
    size({windowSize.x * 0.6f, windowSize.y * 0.05f})
{
    if (instance != nullptr)
    {
        throw std::logic_error("ActionMenu is a singleton class");
    }

    instance = this;
}

void ActionMenu::update()
{
    if (isSpendingCoinsMenuOpen)
    {
        buttons.clear();

        buttons.push_back(ButtonMenu("Buy 100 wood", size, buyResources, {static_cast<void*>(new WoodResource(100))}));
        buttons.push_back(ButtonMenu("Buy 100 mineral", size, buyResources, {static_cast<void*>(new MineralResource(100))}));
        buttons.push_back(ButtonMenu("Buy 100 humans", size, buyResources, {static_cast<void*>(new HumanResource(100))}));
        buttons.push_back(ButtonMenu("Buy 100 food", size, buyResources, {static_cast<void*>(new FoodResource(100))}));
        buttons.push_back(ButtonMenu("Go back", size, buyResources, {static_cast<void*>(new NullResource())}));
    
        organizeButtons();
        return;
    }

    auto piece = GameContext::getTile();
    auto empire = GameContext::getPlayer();

    if (empire == nullptr)
    {
        return;
    }

    buttons.clear();

    if (empire->getTerritory().size() <= 0)
    {
        buttons.push_back(ButtonMenu("(S)elect initial tile", size, selectInitialTileBtnCb, {}));
    }

    if (piece != nullptr)
    {
        if (piece->isOwnedBy(empire->getId()) && piece->isImprovable() && empire->hasResources(piece->getImprovementCost())) 
        {
            buttons.push_back(ButtonMenu("(I)mprove tile", size, improveTileBtnCb, {}));
        }

        if (!piece->isOwnedBySomeone() && empire->isTileNeighbor(piece) && empire->hasResources({HumanResource(GameContext::getTileHrCost())}))
        {
            buttons.push_back(ButtonMenu("(A)nnex tile", size, annexTileBtnCb, {}));
        }

        if (piece->isOwnedBy(empire->getId()) && piece->isConstructable() && empire->hasResources(piece->getConstructionCost()))
        {
            buttons.push_back(ButtonMenu("Construct in tile\n(M)ilitary", size, constructMilitaryTileBtnCb, {}));
            buttons.push_back(ButtonMenu("Construct in tile\n(C)ulture", size, constructCultureTileBtnCb, {}));
            buttons.push_back(ButtonMenu("Construct in tile\n(E)conomy", size, constructEconomyTileBtnCb, {}));
        }

        if (empire->hasResources({GoldResource(1)}))
        {
            buttons.push_back(ButtonMenu("Spend (G)old coins", size, spendGoldCoinBtnCb, {}));
        }
    }

    buttons.push_back(ButtonMenu("(N)ext turn", size, nextTurnBtnCb, {}));

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

    if (!empire->isTileNeighbor(tile))
    {
        std::cout << "New tile must be adjacent to your current territory!" << std::endl;
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

    if (tile->isImprovable() && empire->expendResources(tile->getImprovementCost()))
    {
        tile->improve();
    }
}

void ActionMenu::constructMilitaryTileBtnCb(std::vector<void*> parameters)
{
    constructTile(TilePiece::ConstructionType::MILITARY);
}

void ActionMenu::constructEconomyTileBtnCb(std::vector<void *> parameters)
{
    constructTile(TilePiece::ConstructionType::ECONOMY);
}

void ActionMenu::constructCultureTileBtnCb(std::vector<void *> parameters)
{
    constructTile(TilePiece::ConstructionType::CULTURE);
}

void ActionMenu::spendGoldCoinBtnCb(std::vector<void *> parameters)
{
    Empire* empire = GameContext::getPlayer();

    if (empire == nullptr)
    {
        throw std::logic_error("At least one empire should be selected by now");
    }

    instance->setBuyResourceButtons();
}

void ActionMenu::nextTurnBtnCb(std::vector<void *> parameters)
{
    // TODO: Quando um jogador ganhar, deixar os demais jogarem mais um turno

    GameContext::nextPlayer();
    GameContext::getPlayer()->update(sf::seconds(5));
}

void ActionMenu::buyResources(std::vector<void *> parameters)
{
    Empire* empire = GameContext::getPlayer();

    if (parameters.size() == 0)
    {
        throw std::logic_error("Resource should be passed as parameter");
    }

    Resource* resource = static_cast<Resource*>(parameters[0]);

    if (resource == nullptr)
    {
        throw std::logic_error("A valid resource should be passed as parameter");
    }

    if (empire == nullptr)
    {
        throw std::logic_error("At least one empire should be selected by now");
    }

    if (resource->getAmount() > 0)
    {
        empire->addResource(*resource);
        empire->expendResources({GoldResource(1)});
    }

    instance->isSpendingCoinsMenuOpen = false;
}

void ActionMenu::setBuyResourceButtons()
{
    isSpendingCoinsMenuOpen = true;
}

void ActionMenu::setActionButtons()
{
    buttons.clear();

    organizeButtons();
}

void ActionMenu::constructTile(TilePiece::ConstructionType type)
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
        std::cout << "You should own this tile to construct in it!" << std::endl;
        return;
    }

    empire->createNewConstruction(tile, type);
}
