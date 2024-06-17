#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"

#include <SFML/Graphics.hpp>

class HelpArea : public sf::Drawable
{
public:
    HelpArea(sf::Vector2f viewSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update();
private:
    sf::RectangleShape background;
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

#endif // HELPAREA_HPP
