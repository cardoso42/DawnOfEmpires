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

    static void startGameBtnCb(std::vector<void *> parameters);

    static void addSubMenu(GenericMenu *submenu);
    static void goBackMainMenu();

private:
    sf::Vector2f windowSize;
    static MainMenu* instance;
};

#endif // MAINMENU_HPP
