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

    std::string affirmative = ((previousTile->isOwnedBy(previousEmpire->getId())) ? " " : " do not ");
    createText("You" + affirmative + "own this tile!");

    if (!previousTile->isOwnedBy(previousEmpire->getId()))
    {
        createText("Annexation cost: " + std::to_string(GameContext::getTileHrCost()) + " humans");
    }  
}

void HelpArea::addImprovementTileText()
{
    std::vector<Resource> improvement = previousTile->getImprovementCost();

    if (!previousTile->isImprovable())
    {
        if (previousTile->isModified() && !previousTile->isConstruction())
        {
            createText("Tile already improved", 50);
        }
        else if (previousTile->isConstruction())
        {
            createText("Tile is already a construct", 50);
        }
        else
        {
            createText("Tile cannot be improved", 50);
        }
    }
    else
    {
        createText("Improvement cost", 50);
        listResources(improvement);
    }
}

void HelpArea::addConstuctionTileText()
{
    std::vector<Resource> construction = previousTile->getConstructionCost();

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
