#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "GenericMenu.hpp"
#include "StackMenu.hpp"
#include "GameContext.hpp"

class MainMenu : public StackMenu
{
public:
    MainMenu(sf::Vector2f windowSize);
    ~MainMenu();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static void startGameBtnCb(std::vector<void *> parameters);

    static void addSubMenu(GenericMenu *submenu);
    static void goBackMainMenu();

private:
    sf::Vector2f windowSize;
    AnimatedAsset background;
    static MainMenu* instance;

    const std::vector<std::string> bgImgs = {
        "cristo.png", "coliseu.png", "chichén-itzá.png", "great-wall.png", 
        "taj-mahal.png", "petra.png", "machu-pichu.png"};
    void setRandomBackground();
};

#endif // MAINMENU_HPP
