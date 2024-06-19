#ifndef HELPACTIONSPAGE_HPP
#define HELPACTIONSPAGE_HPP

#include "HelpPage.hpp"
#include <Resources.hpp>
#include "Empire.hpp"
#include "TilePiece.hpp"

class HelpActionsPage : public HelpPage
{
public:
    HelpActionsPage(sf::Vector2f windowSize, sf::Vector2f positionReference);

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<sf::Text> texts;
    sf::Text locator;
    sf::CircleShape currentPlayerColor;
    Empire* currentEmpire;
    TilePiece* currentTile;

    void createText(std::string newText, int yDistance = 20);
    void updateTexts();
    void listResources(std::vector<Resource> resouces);
    void addPlayerText();
    void addAnnexationTileText();
    void addImprovementTileText();
    void addConstuctionTileText();
    void resetTexts();
};

#endif // HELPACTIONSPAGE_HPP
