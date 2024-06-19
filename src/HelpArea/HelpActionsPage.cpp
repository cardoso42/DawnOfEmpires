#include "HelpActionsPage.hpp"

#include "AssetManager.hpp"
#include "GameContext.hpp"

HelpActionsPage::HelpActionsPage(sf::Vector2f windowSize) : HelpPage(windowSize) { }

void HelpActionsPage::update()
{
    Empire* selectedEmpire = GameContext::getPlayer();
    TilePiece* selectedTile = GameContext::getTile();

    if (selectedEmpire == currentEmpire && selectedTile == currentTile)
    {
        return;
    }

    currentEmpire = selectedEmpire;
    currentTile = selectedTile;
    updateTexts();
}

void HelpActionsPage::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    HelpPage::draw(target, states);
    target.draw(currentPlayerColor);
}

void HelpActionsPage::updateTexts()
{
    resetTexts();

    if (currentEmpire == nullptr)
    {
        return;
    }

    addPlayerText();

    if (currentTile == nullptr)
    {
        return;
    }

    addAnnexationTileText(); 
    addImprovementTileText();
    addConstuctionTileText();
}

void HelpActionsPage::listResources(std::vector<Resource> resources)
{
    for (auto resource : resources)
    {
        std::string str = resource.getName() + ": " + std::to_string(static_cast<int>(resource.getAmount()));
        createText(str);
    }
}

void HelpActionsPage::addPlayerText()
{
    const int radius = 8;

    createText("Player " + std::to_string(currentEmpire->getId()) + " turn", 10);

    currentPlayerColor = sf::CircleShape(radius);
    currentPlayerColor.setFillColor(currentEmpire->getColor());
    currentPlayerColor.setOrigin({radius * 0.5f, radius * 0.5f});
    currentPlayerColor.setPosition(size.x * 0.55f, size.y + 17);
}

void HelpActionsPage::addAnnexationTileText()
{
    createText(currentTile->getTypeName() + " tile", 40);

    bool playerOwnsTile = currentTile->isOwnedBy(currentEmpire->getId());

    std::string affirmative = (playerOwnsTile ? " " : " do not ");
    createText("You" + affirmative + "own this tile!");

    if (playerOwnsTile)
    {
        return;
    }

    if (currentTile->isOwnedBySomeone())
    {
        createText("It belongs to another player");
    }
    else if (currentEmpire->getTerritory().size() == 0)
    {
        createText("Start your empire here");
    }
    else
    {
        if (currentEmpire->isTileNeighbor(currentTile))
        {
            createText("You can annex this tile");
        }
        else
        {
            createText("Unnaxebale, not adjacent");
        }

        createText("Annexation cost: " + std::to_string(GameContext::getTileHrCost()) + " humans");
    }
}

void HelpActionsPage::addImprovementTileText()
{
    std::vector<Resource> improvement = currentTile->getImprovementCost();

    if (currentTile->isOwnedBySomeone() && !currentTile->isOwnedBy(currentEmpire->getId()))
    {
        return;
    }

    if (currentTile->isImprovable())
    {
        createText("Improvement cost", 40);
        listResources(improvement);
        return;
    }

    if (currentTile->isModified() && !currentTile->isConstruction())
    {
        createText("Tile already improved", 40);
    }
    else if (currentTile->isConstruction())
    {
        createText("Tile is already a construction", 40);
    }
    else
    {
        createText("Tile cannot be improved", 40);
    }
}

void HelpActionsPage::addConstuctionTileText()
{
    std::vector<Resource> construction = currentTile->getConstructionCost();

    if (currentTile->isOwnedBySomeone() && !currentTile->isOwnedBy(currentEmpire->getId()))
    {
        return;
    }

    if (!currentTile->isConstructable())
    {
        createText("Tile cannot be constructed", 40);
    }
    else
    {
        createText("Construction cost", 40);
        listResources(construction);
    }
}

// TODO: do not allow the player to set its starting territory in someone else's land
