#ifndef SETTINGSPAGE_HPP
#define SETTINGSPAGE_HPP

#include "GenericMenu.hpp"
#include "Callbacks.hpp"
#include <WindowManager.hpp>
#include <cassert>

class SettingsPage : public GenericMenu
{
public:
    SettingsPage(sf::Vector2f windowSize) : windowSize(windowSize), GenericMenu(windowSize, sf::Color(255, 255, 255, 180))
    {
        addIncDecControl(new IncrementDecrementControl(
            {windowSize.x * 0.8f, windowSize.y * 0.05f}, "Players", 
            &numPlayers, 1, GameContext::getMaxPlayersNumber()));

        addIncDecControl(new IncrementDecrementControl(
            {windowSize.x * 0.8f, windowSize.y * 0.05f}, "Map size", 
            &mapSize, 1, GameContext::getMaxMapSize()));

        addButton("Go back", [](std::vector<void *> parameters) { MainMenu::goBackMainMenu(); }, {});
        addButton("Start game", MainMenu::startGameBtnCb, {});

        organizeMenu();
    }

    ~SettingsPage()
    {
        GameContext::setNumPlayers(numPlayers);
        GameContext::setMapSize(mapSize);
    }

    std::string getName() override { return "SettingsPage"; }

private:
    sf::Vector2f windowSize;

    int numPlayers{GameContext::getPlayersNumber()};
    int mapSize{GameContext::getMapSize()};
};

#endif // SETTINGSPAGE_HPP
