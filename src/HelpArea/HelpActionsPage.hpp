#ifndef HELPACTIONSPAGE_HPP
#define HELPACTIONSPAGE_HPP

#include "HelpPage.hpp"
#include <Resources.hpp>
#include "Empire.hpp"
#include "TilePiece.hpp"

class HelpActionsPage : public HelpPage
{
public:
    HelpActionsPage(sf::Vector2f windowSize);

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::CircleShape currentPlayerColor;
    Empire* currentEmpire;
    TilePiece* currentTile;

    void updateTexts();
    void listResources(std::vector<Resource> resouces);
    void addPlayerText();
    void addAnnexationTileText();
    void addImprovementTileText();
    void addConstuctionTileText();
};

#endif // HELPACTIONSPAGE_HPP
