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

        const sf::Vector2f buttonSize(windowSize.x * 0.3f, windowSize.y * 0.1f);

        setButtonSize(buttonSize);

        addButton("Start", Callbacks::startGameBtnCb, {});
        addButton("Settings", Callbacks::settingsBtnCb, {reinterpret_cast<void*>(&SettingsPageFactory), static_cast<void*>(&size)});
        addButton("Exit", Callbacks::exitGameBtnCb, {});

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