#ifndef HELPAREA_HPP
#define HELPAREA_HPP

#include "TilePiece.hpp"
#include "Empire.hpp"
#include "HelpPage.hpp"
#include "BaseComponent.hpp"

#include <SFML/Graphics.hpp>

// TODO: Add something to tell the user that he can change the page on the help area

class HelpArea : public BaseComponent
{
public:
    HelpArea(sf::Vector2f viewSize);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void animate(sf::Time deltaTime) override;
    void update() override;
    void click(float x, float y) override;
    void handleKeyboardInput(sf::Keyboard::Key key) override;

private:
    sf::RectangleShape background;
    std::vector<HelpPage*> pages;
    int currentPage = 0;
};

#endif // HELPAREA_HPP
