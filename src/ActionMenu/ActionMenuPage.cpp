#include "ActionMenuPage.hpp"
#include <GameContext.hpp>

ActionMenuPage::ActionMenuPage(sf::Vector2f size) : size(size) { }

ActionMenuPageMain::ActionMenuPageMain(sf::Vector2f size) : ActionMenuPage(size) { }

std::vector<ButtonMenu> ActionMenuPageMain::getButtons()
{
    std::vector<ButtonMenu> buttons;
    auto piece = GameContext::getTile();
    auto empire = GameContext::getPlayer();

    if (empire == nullptr)
    {
        return;
    }
    
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
}

ActionMenuPageSpendCoins::ActionMenuPageSpendCoins(sf::Vector2f size) : ActionMenuPage(size) { }

std::vector<ButtonMenu> ActionMenuPageSpendCoins::getButtons()
{
    return std::vector<ButtonMenu>();
}

void ActionMenuPageMain::annexTileBtnCb(std::vector<void *> parameters)
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

void ActionMenuPageMain::selectInitialTileBtnCb(std::vector<void *> parameters)
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

void ActionMenuPageMain::improveTileBtnCb(std::vector<void*> parameters)
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

void ActionMenuPageMain::constructMilitaryTileBtnCb(std::vector<void*> parameters)
{
    constructTile(TilePiece::ConstructionType::MILITARY);
}

void ActionMenuPageMain::constructEconomyTileBtnCb(std::vector<void *> parameters)
{
    constructTile(TilePiece::ConstructionType::ECONOMY);
}

void ActionMenuPageMain::constructCultureTileBtnCb(std::vector<void *> parameters)
{
    constructTile(TilePiece::ConstructionType::CULTURE);
}

void ActionMenuPageMain::spendGoldCoinBtnCb(std::vector<void *> parameters)
{
    Empire* empire = GameContext::getPlayer();

    if (empire == nullptr)
    {
        throw std::logic_error("At least one empire should be selected by now");
    }

    instance->setBuyResourceButtons();
}

void ActionMenuPageMain::nextTurnBtnCb(std::vector<void *> parameters)
{
    // TODO: Quando um jogador ganhar, deixar os demais jogarem mais um turno

    GameContext::nextPlayer();
    GameContext::getPlayer()->update(sf::seconds(5));
}

void ActionMenuPageMain::constructTile(TilePiece::ConstructionType type)
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
