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

    static void startGameBtnCb(std::vector<void *> parameters)
    {
        GameContext::startGame();
    }

    static void addSubMenu(GenericMenu *submenu);
    static void goBack();
private:
    static MainMenu* instance;
};

#endif // MAINMENU_HPP
