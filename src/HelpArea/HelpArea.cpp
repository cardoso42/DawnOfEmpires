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

    target.draw(currentPlayerColor);
}

void HelpArea::update()
{
    Empire* selectedEmpire = GameContext::getPlayer();
    TilePiece* selectedTile = GameContext::getTile();

    if (selectedEmpire == currentEmpire && selectedTile == currentTile)
    {
        return;
    }
    else
    {
        currentEmpire = selectedEmpire;
        currentTile = selectedTile;
    }

    updateTexts();
}

void HelpArea::updateTexts()
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
    const int radius = 8;

    createText("Player " + std::to_string(currentEmpire->getId()) + " turn", 10);

    currentPlayerColor = sf::CircleShape(radius);
    currentPlayerColor.setFillColor(currentEmpire->getColor());
    currentPlayerColor.setOrigin({radius * 0.5f, radius * 0.5f});
    currentPlayerColor.setPosition(background.getPosition().x + background.getLocalBounds().width * 0.55f, background.getPosition().y + 17);
}

void HelpArea::addAnnexationTileText()
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

void HelpArea::addImprovementTileText()
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

void HelpArea::addConstuctionTileText()
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
