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
    ~ActionMenu();

    void update();
    
    static void annexTileBtnCb(std::vector<void*> parameters);
    static void selectInitialTileBtnCb(std::vector<void*> parameters);
    static void improveTileBtnCb(std::vector<void*> parameters);
    static void constructMilitaryTileBtnCb(std::vector<void*> parameters);
    static void constructEconomyTileBtnCb(std::vector<void*> parameters);
    static void constructCultureTileBtnCb(std::vector<void*> parameters);
    static void spendGoldCoinBtnCb(std::vector<void*> parameters);
    static void nextTurnBtnCb(std::vector<void*> parameters);

    static void buyResources(std::vector<void *> parameters);
private:
    sf::Vector2f size;
    void setBuyResourceButtons();
    void setActionButtons();
    bool isSpendingCoinsMenuOpen = false;

    static void constructTile(TilePiece::ConstructionType type);
    static ActionMenu* instance;
};

#endif // ACTIONMENU_HPP
