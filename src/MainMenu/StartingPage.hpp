#ifndef STARTINGPAGE_HPP
#define STARTINGPAGE_HPP

#include "GenericMenu.hpp"
#include "SettingsPage.hpp"
#include "Callbacks.hpp"

class StartingPage : public GenericMenu
{
public:
    StartingPage(sf::Vector2f windowSize) : GenericMenu(windowSize, sf::Color(255, 255, 255, 180)), size(windowSize)
    {
        setRandomBackground();
        setActions();
    }

    void setActions() override
    {
        const sf::Vector2f buttonSize(size.x * 0.3f, size.y * 0.1f);
        setButtonSize(buttonSize);

        clearMenu();

        addButton("(P)lay", Callbacks::startGameBtnCb, {});
        GameContext::addKeyAction(sf::Keyboard::P, Callbacks::startGameBtnCb);
        addButton("(S)ettings", Callbacks::settingsBtnCb, {reinterpret_cast<void*>(&SettingsPageFactory), static_cast<void*>(&size)});
        GameContext::addKeyAction(sf::Keyboard::S, Callbacks::settingsBtnCb, {reinterpret_cast<void*>(&SettingsPageFactory), static_cast<void*>(&size)});
        addButton("(E)xit", Callbacks::exitGameBtnCb, {});
        GameContext::addKeyAction(sf::Keyboard::E, Callbacks::exitGameBtnCb);

        organizeMenu();
    }

    void update() override 
    {
    }

    std::string getName() override { return "StartingPage"; }

    void animate(sf::Time deltaTime) override {}
private:
    sf::Vector2f size;
    static SettingsPage* SettingsPageFactory(sf::Vector2f size) { return new SettingsPage(size); }
};

#endif // STARTINGPAGE_HPP