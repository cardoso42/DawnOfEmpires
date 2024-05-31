#ifndef ACTIONMENU_HPP
#define ACTIONMENU_HPP

#include "ButtonMenu.hpp"
#include "GenericMenu.hpp"
#include "Empire.hpp"
#include "TilePiece.hpp"

#include "SFML/Graphics.hpp"

class ActionMenu : public GenericMenu
{
public:
    ActionMenu(sf::Vector2f windowSize);
    static void annexTileBtnCb(std::vector<void*> parameters);
    static void selectInitialTileBtnCb(std::vector<void*> parameters);
    static void improveTileBtnCb(std::vector<void*> parameters);
    static void constructTileBtnCb(std::vector<void*> parameters);
private:
};

#endif // ACTIONMENU_HPP
