#include "HelpArea.hpp"

#include "GameContext.hpp"

HelpArea::HelpArea(sf::Vector2f viewSize) : background(viewSize)
{
    background.setFillColor(sf::Color(0, 0, 0, 200));
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

    texts.clear();

    if (selectedEmpire == nullptr)
    {
        return;
    }

    sf::Text playerTurn("Player " + std::to_string(selectedEmpire->getId()) + " turn", AssetManager::GetFont("anonymous.ttf"), 20);
    playerTurn.setPosition(background.getPosition().x + 10, background.getPosition().y + 10);
    texts.push_back(playerTurn);

    if (selectedTile == nullptr)
    {
        return;
    }

    std::string affirmative = ((selectedTile->isOwnedBy(selectedEmpire->getId())) ? " " : " do not ");
    createText("You" + affirmative + "own this tile!", true);

    if (!selectedTile->isOwnedBy(selectedEmpire->getId()))
    {
        createText("Annexation cost: " + std::to_string(GameContext::getTileHrCost()) + " humans");
    }   

    std::vector<Resource> improvement = selectedTile->getImprovementCost();
    std::vector<Resource> construction = selectedTile->getConstructionCost();

    if (!selectedTile->isImprovable())
    {
        if (selectedTile->isModified() && !selectedTile->isConstruction())
        {
            createText("Tile already improved", true);
        }
        else if (selectedTile->isConstruction())
        {
            createText("Tile is already a construct", true);
        }
        else
        {
            createText("Tile cannot be improved", true);
        }
    }
    else
    {
        createText("Improvement cost", true);
        for (int i = 0; i < improvement.size(); i++)
        {
            std::string resourceStr = improvement[i].getName() + ": " + std::to_string(static_cast<int>(improvement[i].getAmount()));
            createText(resourceStr);
        }
    }

    if (!selectedTile->isConstructable())
    {
        createText("Tile cannot be constructed", true);
    }
    else
    {
        createText("Construction cost", true);
        for (int i = 0; i < construction.size(); i++)
        {
            std::string resourceStr = construction[i].getName() + ": " + std::to_string(static_cast<int>(construction[i].getAmount()));
            createText(resourceStr);
        }
    }
}

void HelpArea::createText(std::string newText, bool newSection)
{
    sf::Text text(newText, AssetManager::GetFont("anonymous.ttf"), 20);
    text.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + (newSection ? 50 : 20));
    texts.push_back(text);
}
