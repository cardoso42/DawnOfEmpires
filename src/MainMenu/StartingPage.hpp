#ifndef STARTINGPAGE_HPP
#define STARTINGPAGE_HPP

#include "GenericMenu.hpp"
#include "Callbacks.hpp"

class StartingPage : public GenericMenu
{
// TODO: save/load mechanisms

public:
    StartingPage(sf::Vector2f windowSize) : GenericMenu(windowSize)
    {
        const sf::Vector2f buttonSize(windowSize.x * 0.3f, windowSize.y * 0.1f);

        setButtonSize(buttonSize);

        addButton("Start", MainMenu::startGameBtnCb, {});
        addButton("Settings", Callbacks::settingsBtnCb, {});
        addButton("Exit", Callbacks::exitGameBtnCb, {});

        organizeButtons();
    }

    void update() override 
    {
    }

    std::string getName() override { return "StartingPage"; }

    void animate(sf::Time deltaTime) override {}
};

#endif // STARTINGPAGE_HPP