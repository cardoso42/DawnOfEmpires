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
    sf::Text owner("You" + affirmative + "own this tile!" , AssetManager::GetFont("anonymous.ttf"), 20);
    owner.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 50);
    texts.push_back(owner);

    if (!selectedTile->isOwnedBy(selectedEmpire->getId()))
    {
        sf::Text annexationCost = sf::Text("Annexation cost: 1 human", AssetManager::GetFont("anonymous.ttf"), 20);
        annexationCost.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 20);
        texts.push_back(annexationCost);
    }   

    std::vector<Resource> improvement = selectedTile->getImprovementCost();
    std::vector<Resource> construction = selectedTile->getConstructionCost();

    if (!selectedTile->isImprovable())
    {
        if (selectedTile->isModified() && !selectedTile->isConstruction())
        {
            sf::Text improvementTitle("Tile already improved", AssetManager::GetFont("anonymous.ttf"), 20);
            improvementTitle.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 50);
            texts.push_back(improvementTitle);
        }
        else if (selectedTile->isConstruction())
        {
            sf::Text improvementTitle("Tile is alreay a construction", AssetManager::GetFont("anonymous.ttf"), 20);
            improvementTitle.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 50);
            texts.push_back(improvementTitle);
        }
        else
        {
            sf::Text improvementTitle("Tile cannot be improved", AssetManager::GetFont("anonymous.ttf"), 20);
            improvementTitle.setPosition(background.getPosition().x + 10, texts.back().getPosition().y+ 50);
            texts.push_back(improvementTitle);
        }
    }
    else
    {
        sf::Text improvementTitle("Improvement cost", AssetManager::GetFont("anonymous.ttf"), 20);
        improvementTitle.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 50);
        texts.push_back(improvementTitle);
        for (int i = 0; i < improvement.size(); i++)
        {
            std::string resourceStr = improvement[i].getName() + ": " + std::to_string(static_cast<int>(improvement[i].getAmount()));
            sf::Text resource(resourceStr, AssetManager::GetFont("anonymous.ttf"), 20);
            resource.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 20);
            texts.push_back(resource);
        }
    }

    if (!selectedTile->isConstructable())
    {
        sf::Text improvementTitle("Tile cannot be constructed", AssetManager::GetFont("anonymous.ttf"), 20);
        improvementTitle.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 50);
        texts.push_back(improvementTitle);
    }
    else
    {
        sf::Text constructionTitle("Construction cost", AssetManager::GetFont("anonymous.ttf"), 20);
        constructionTitle.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 50);
        texts.push_back(constructionTitle);
        for (int i = 0; i < construction.size(); i++)
        {
            std::string resourceStr = construction[i].getName() + ": " + std::to_string(static_cast<int>(construction[i].getAmount()));
            sf::Text resource(resourceStr, AssetManager::GetFont("anonymous.ttf"), 20);
            resource.setPosition(background.getPosition().x + 10, texts.back().getPosition().y + 20);
            texts.push_back(resource);
        }
    }
}
