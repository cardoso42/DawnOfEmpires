#ifndef STARTINGPAGE_HPP
#define STARTINGPAGE_HPP

#include "GenericMenu.hpp"
#include "Callbacks.hpp"

class StartingPage : public GenericMenu
{
public:
    StartingPage(sf::Vector2f windowSize) : GenericMenu(windowSize, sf::Color(255, 255, 255, 180))
    {
        setRandomBackground();

        const sf::Vector2f buttonSize(windowSize.x * 0.3f, windowSize.y * 0.1f);

        setButtonSize(buttonSize);

        addButton("Start", MainMenu::startGameBtnCb, {});
        addButton("Settings", Callbacks::settingsBtnCb, {});
        addButton("Exit", Callbacks::exitGameBtnCb, {});

        organizeMenu();
    }

    void update() override 
    {
    }

    std::string getName() override { return "StartingPage"; }

    void animate(sf::Time deltaTime) override {}
};

#endif // STARTINGPAGE_HPP