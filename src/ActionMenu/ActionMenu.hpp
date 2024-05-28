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
    ActionMenu(sf::Vector2f windowSize, Empire *currentEmpire, TilePiece *currentTile);
private:
    static void selectInitialTileBtnCb(std::vector<void*> parameters);
    static void improveTileBtnCb(std::vector<void*> parameters);
};

#endif // ACTIONMENU_HPP
