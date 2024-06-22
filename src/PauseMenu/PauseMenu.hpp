#ifndef PAUSEMENU_HPP
#define PAUSEMENU_HPP

#include "GenericMenu.hpp"

class PauseMenu : public GenericMenu
{
public:
    PauseMenu(sf::Vector2f windowSize);
private:
    static void resumeBtnCb(std::vector<void *> parameters);
    static void exitBtnCb(std::vector<void *> parameters);
};

#endif // PAUSEMENU_HPP
