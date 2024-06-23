#ifndef SETTINGSPAGE_HPP
#define SETTINGSPAGE_HPP

#include <cassert>

#include <WindowManager.hpp>
#include "GenericMenu.hpp"
#include "Callbacks.hpp"

// TODO: bug when all tiles are already occupied and there is tile obtention with military constructions
// Maybe change mechanics to occupy all tiles in a radius of 2 instantly

class SettingsPage : public GenericMenu
{
public:
    SettingsPage(sf::Vector2f windowSize) : windowSize(windowSize), GenericMenu(windowSize, sf::Color(255, 255, 255, 180))
    {
        setRandomBackground();
        setActions();
    }

    void setActions() override
    {
        clearMenu();

        setButtonSize({windowSize.x * 0.3f, windowSize.y * 0.1f});

        addButton("Go (B)ack", goBackCb, {&numPlayers, &mapSize});
        GameContext::addKeyAction(sf::Keyboard::B, goBackCb, {&numPlayers, &mapSize});

        addIncDecControl(new IncrementDecrementControl(
            {windowSize.x * 0.8f, windowSize.y * 0.05f}, "Players", 
            &numPlayers, 1, GameContext::getMaxPlayersNumber()));

        addIncDecControl(new IncrementDecrementControl(
            {windowSize.x * 0.8f, windowSize.y * 0.05f}, "Map size", 
            &mapSize, 1, GameContext::getMaxMapSize()));

        addButton("(S)tart game", startCb, {&numPlayers, &mapSize});
        GameContext::addKeyAction(sf::Keyboard::S, startCb, {&numPlayers, &mapSize});

        organizeMenu();
    }

    static void goBackCb(CallbackParameters parameters)
    {
        GameContext::setNumPlayers(*(int*)parameters[0]);
        GameContext::setMapSize(*(int*)parameters[1]);
        MainMenu::goBackMainMenu(); 
    }

    static void startCb(CallbackParameters parameters)
    {
        GameContext::setNumPlayers(*(int*)parameters[0]); 
        GameContext::setMapSize(*(int*)parameters[1]); 
        Callbacks::startGameBtnCb({}); 
    }

    std::string getName() override { return "SettingsPage"; }

private:
    sf::Vector2f windowSize;

    int numPlayers{GameContext::getPlayersNumber()};
    int mapSize{GameContext::getMapSize()};
};

#endif // SETTINGSPAGE_HPP
