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

    buttons.push_back(ButtonMenu("(S)elect initial tile", size, selectInitialTileBtnCb, {}));
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

    bool isAdjacent{false};
    for (auto neighbor : tile->getNeighbors())
    {
        if (neighbor->isOwnedBy(empire->getId()))
        {
            isAdjacent = true;
        }
    }

    if (!isAdjacent)
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
    instance->setActionButtons();

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

    instance->setActionButtons();
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
    // TODO: Fazer com que botões do menu sejam dinâmicos de acordo com o contexto
    // TODO: Mostrar custo de anexação apenas caso não seja de nenhum jogador
    // TODO: Randomizar cores dos jogadores
    // TODO: Mostrar cor do jogador atual no menu de ajuda
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

    instance->setActionButtons();
}

void ActionMenu::setBuyResourceButtons()
{
    buttons.clear();

    buttons.push_back(ButtonMenu("Buy 100 wood", size, buyResources, {static_cast<void*>(new WoodResource(100))}));
    buttons.push_back(ButtonMenu("Buy 100 mineral", size, buyResources, {static_cast<void*>(new MineralResource(100))}));
    buttons.push_back(ButtonMenu("Buy 100 humans", size, buyResources, {static_cast<void*>(new HumanResource(100))}));
    buttons.push_back(ButtonMenu("Buy 100 food", size, buyResources, {static_cast<void*>(new FoodResource(100))}));
    buttons.push_back(ButtonMenu("Go back", size, buyResources, {static_cast<void*>(new NullResource())}));

    organizeButtons();
}

void ActionMenu::setActionButtons()
{
    buttons.clear();

    buttons.push_back(ButtonMenu("(I)mprove tile", size, improveTileBtnCb, {}));
    buttons.push_back(ButtonMenu("(A)nnex tile", size, annexTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Construct in tile\n(M)ilitary", size, constructMilitaryTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Construct in tile\n(C)ulture", size, constructCultureTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Construct in tile\n(E)conomy", size, constructEconomyTileBtnCb, {}));
    buttons.push_back(ButtonMenu("Spend (G)old coins", size, spendGoldCoinBtnCb, {}));
    buttons.push_back(ButtonMenu("(N)ext turn", size, nextTurnBtnCb, {}));

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
