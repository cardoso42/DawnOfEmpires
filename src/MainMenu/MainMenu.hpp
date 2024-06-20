#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "GenericMenu.hpp"

class MainMenu : public GenericMenu
{
public:
    MainMenu(sf::Vector2f windowSize);

    void update() override {}
    void animate(sf::Time deltaTime) override {}

private:
    static void startGameBtnCb(std::vector<void *> parameters);
    static void loadGameBtnCb(std::vector<void *> parameters);
    static void settingsBtnCb(std::vector<void *> parameters);
    static void exitGameBtnCb(std::vector<void *> parameters);
};

#endif // MAINMENU_HPP
