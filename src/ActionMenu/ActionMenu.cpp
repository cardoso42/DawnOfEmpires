#include "ActionMenu.hpp"
#include <iostream>
#include "GameContext.hpp"

ActionMenu* ActionMenu::instance = nullptr;

ActionMenu::ActionMenu(sf::Vector2f windowSize) : size(windowSize),
    GenericMenu(windowSize, sf::Color(191, 191, 191))
{
    if (instance != nullptr)
    {
        throw std::logic_error("ActionMenu is a singleton class");
    }

    instance = this;

    setButtonSize({size.x * 0.6f, size.y * 0.05f});
}

ActionMenu::~ActionMenu()
{
    instance = nullptr;
}

void ActionMenu::update()
{
    if (isSpendingCoinsMenuOpen)
    {
        clearButtons();

        addButton("Buy 500 wood", buyResources, {new WoodResource(500)});
        addButton("Buy 100 mineral", buyResources, {new MineralResource(100)});
        addButton("Buy 30 humans", buyResources, {new HumanResource(30)});
        addButton("Buy 50 food", buyResources, {new FoodResource(50)});
        addButton("Go back", buyResources, {new NullResource()});
    
        organizeButtons();
        return;
    }

    auto piece = GameContext::getTile();
    auto empire = GameContext::getPlayer();

    if (empire == nullptr)
    {
        return;
    }

    clearButtons();

    if (empire->getTerritory().size() <= 0)
    {
        addButton("(S)elect initial tile", selectInitialTileBtnCb, {});
        GameContext::addKeyAction(sf::Keyboard::S, selectInitialTileBtnCb);
    }

    if (piece != nullptr)
    {
        if (piece->isOwnedBy(empire->getId()) && piece->isImprovable() && empire->hasResources(piece->getImprovementCost())) 
        {
            addButton("(I)mprove tile", improveTileBtnCb, {});
            GameContext::addKeyAction(sf::Keyboard::I, improveTileBtnCb);
        }

        if (!piece->isOwnedBySomeone() && empire->isTileNeighbor(piece) && empire->hasResources({HumanResource(GameContext::getTileHrCost())}))
        {
            addButton("(A)nnex tile", annexTileBtnCb, {});
            GameContext::addKeyAction(sf::Keyboard::A, annexTileBtnCb);
        }

        if (piece->isOwnedBy(empire->getId()) && piece->isConstructable() && empire->hasResources(piece->getConstructionCost()))
        {
            addButton("Construct in tile\n(M)ilitary", constructMilitaryTileBtnCb, {});
            GameContext::addKeyAction(sf::Keyboard::M, constructMilitaryTileBtnCb);
            addButton("Construct in tile\n(C)ulture", constructCultureTileBtnCb, {});
            GameContext::addKeyAction(sf::Keyboard::C, constructCultureTileBtnCb);
            addButton("Construct in tile\n(E)conomy", constructEconomyTileBtnCb, {});
            GameContext::addKeyAction(sf::Keyboard::E, constructEconomyTileBtnCb);
        }

        if (empire->hasResources({GoldResource(1)}))
        {
            addButton("Spend (G)old coins", spendGoldCoinBtnCb, {});
            GameContext::addKeyAction(sf::Keyboard::G, spendGoldCoinBtnCb);
        }
    }

    addButton("(N)ext turn", nextTurnBtnCb, {});
    GameContext::addKeyAction(sf::Keyboard::N, nextTurnBtnCb);
#ifdef DEBUG
    CallbackFunction cb = [](std::vector<void*> parameters) {
        for (int i = 0; i < 100; i++)
        {
            GameContext::nextPlayer();
            GameContext::getPlayer()->update(sf::seconds(5));
        }
    };
    addButton("Advance (1)00 turns", cb, {});
    GameContext::addKeyAction(sf::Keyboard::Num1, cb);
#endif

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

    if (tile->isOwnedBySomeone())
    {
        std::cout << "You can only use an unclaimed tile to start your empire" << std::endl;
        return;
    }

    for (auto neighbor : tile->getNeighbors())
    {
        if (neighbor->isOwnedBySomeone())
        {
            std::cout << "All neighbors of your selected tile must be unclaimed" << std::endl;
            return;
        }
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
