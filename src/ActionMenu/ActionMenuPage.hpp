#ifndef ACTIONMENUPAGE_HPP
#define ACTIONMENUPAGE_HPP

#include "ButtonMenu.hpp"

#include "SFML/Graphics.hpp"

class ActionMenuPage
{
public:
    ActionMenuPage(sf::Vector2f size);

    virtual std::vector<ButtonMenu> getButtons() = 0;

protected:
    sf::Vector2f size;
};

class ActionMenuPageMain : public ActionMenuPage
{
public:
    ActionMenuPageMain(sf::Vector2f size);

    std::vector<ButtonMenu> getButtons() override;

    static void annexTileBtnCb(std::vector<void*> parameters);
    static void selectInitialTileBtnCb(std::vector<void*> parameters);
    static void improveTileBtnCb(std::vector<void*> parameters);
    static void constructMilitaryTileBtnCb(std::vector<void*> parameters);
    static void constructEconomyTileBtnCb(std::vector<void*> parameters);
    static void constructCultureTileBtnCb(std::vector<void*> parameters);
    static void spendGoldCoinBtnCb(std::vector<void*> parameters);
    static void nextTurnBtnCb(std::vector<void*> parameters);

private:
    static void constructTile(TilePiece::ConstructionType type);
};

class ActionMenuPageSpendCoins : public ActionMenuPage
{
public:
    ActionMenuPageSpendCoins(sf::Vector2f size);

    std::vector<ButtonMenu> getButtons() override;
};

#endif // ACTIONMENUPAGE_HPP
