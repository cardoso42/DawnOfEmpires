#include "HelpArea.hpp"

#include "GameContext.hpp"

HelpArea::HelpArea(sf::Vector2f viewSize) : background(viewSize)
{
    background.setFillColor(sf::Color(0, 0, 0, 200));
    
    locator = sf::Text("", AssetManager::GetFont("anonymous.ttf"));
    locator.setPosition({background.getPosition().x + 10, background.getPosition().y});
    texts.push_back(locator);
}

void HelpArea::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    
    for (auto& text : texts)
    {
        target.draw(text);
    }
}

void HelpArea::update()
{
    Empire* selectedEmpire = GameContext::getPlayer();
    TilePiece* selectedTile = GameContext::getTile();

    if (selectedEmpire == previousEmpire && selectedTile == previousTile)
    {
        return;
    }
    else
    {
        previousEmpire = selectedEmpire;
        previousTile = selectedTile;
    }

    updateTexts();
}

void HelpArea::updateTexts()
{
    resetTexts();

    if (previousEmpire == nullptr)
    {
        return;
    }

    addPlayerText();

    if (previousTile == nullptr)
    {
        return;
    }

    addAnnexationTileText(); 
    addImprovementTileText();
    addConstuctionTileText();
}

void HelpArea::listResources(std::vector<Resource> resources)
{
    for (auto resource : resources)
    {
        std::string str = resource.getName() + ": " + std::to_string(static_cast<int>(resource.getAmount()));
        createText(str);
    }
}

void HelpArea::addPlayerText()
{
    createText("Player " + std::to_string(previousEmpire->getId()) + " turn", 10);
}

void HelpArea::addAnnexationTileText()
{
    createText(previousTile->getTypeName() + " tile", 50);

    bool playerOwnsTile = previousTile->isOwnedBy(previousEmpire->getId());

    std::string affirmative = (playerOwnsTile ? " " : " do not ");
    createText("You" + affirmative + "own this tile!");

    if (playerOwnsTile)
    {
        return;
    }

    if (previousTile->isOwnedBySomeone())
    {
        createText("It belongs to another player", 50);
    }
    else
    {
        createText("Annexation cost: " + std::to_string(GameContext::getTileHrCost()) + " humans");
    }
}

void HelpArea::addImprovementTileText()
{
    std::vector<Resource> improvement = previousTile->getImprovementCost();

    if (previousTile->isOwnedBySomeone() && !previousTile->isOwnedBy(previousEmpire->getId()))
    {
        return;
    }

    if (previousTile->isImprovable())
    {
        createText("Improvement cost", 50);
        listResources(improvement);
        return;
    }

    if (previousTile->isModified() && !previousTile->isConstruction())
    {
        createText("Tile already improved", 50);
    }
    else if (previousTile->isConstruction())
    {
        createText("Tile is already a construction", 50);
    }
    else
    {
        createText("Tile cannot be improved", 50);
    }
}

void HelpArea::addConstuctionTileText()
{
    std::vector<Resource> construction = previousTile->getConstructionCost();

    if (previousTile->isOwnedBySomeone() && !previousTile->isOwnedBy(previousEmpire->getId()))
    {
        return;
    }

    if (!previousTile->isOwnedBy(previousEmpire->getId()))
    {
        return;
    }
    if (!previousTile->isConstructable())
    {
        createText("Tile cannot be constructed", 50);
    }
    else
    {
        createText("Construction cost", 50);
        listResources(construction);
    }
}

// TODO: do not allow the player to set its starting territory in someone else's land

void HelpArea::resetTexts()
{
    texts.clear();
    texts.push_back(locator);
}

void HelpArea::createText(std::string newText, int yDistance)
{
    sf::Text text(newText, AssetManager::GetFont("anonymous.ttf"), 20);
    text.setPosition(texts.back().getPosition().x, texts.back().getPosition().y + yDistance);
    texts.push_back(text);
}
