#ifndef SETTINGSPAGE_HPP
#define SETTINGSPAGE_HPP

#include "GenericMenu.hpp"
#include "Callbacks.hpp"
#include <WindowManager.hpp>

class SettingsPage : public GenericMenu
{
public:
    SettingsPage(sf::Vector2f windowSize) : windowSize(windowSize), GenericMenu(windowSize)
    {
        // First column (decrease buttons + go back))
        setButtonSize({windowSize.y * 0.1f, windowSize.y * 0.1f});
        addButton("-", subPlayers, {});
        addButton("-", subMapSize, {});
        addButton("Go back", [](std::vector<void *> parameters) { MainMenu::goBack(); }, {});
        startNewColumn();

        // Middle column (variable values)
        setButtonSize({windowSize.x * 0.2f, windowSize.y * 0.1f});
        addButton("Jogadores: " + std::to_string(GameContext::getPlayersNumber()), nullptr, {});
        addButton("Tamanho do mapa: " + std::to_string(GameContext::getMapSize()), nullptr, {});
        addButton(ButtonMenu("", {0,0})); // empty button to fill the column
        startNewColumn();

        for (auto& button : buttons[1])
        {
            button.setSelectable(false);
            button.setOutlineThickness(0); // Disguise the buttons as just text
        }

        // Last column (increase buttons + start game)
        setButtonSize({windowSize.y * 0.1f, windowSize.y * 0.1f});
        addButton("+", addPlayers, {});
        addButton("+", addMapSize, {});
        addButton("Start game", MainMenu::startGameBtnCb, {});

        organizeButtons();
    }

    void update() override
    {
        buttons[1][0].updateText("Jogadores: " + std::to_string(GameContext::getPlayersNumber()));
        buttons[1][1].updateText("Tamanho do mapa: " + std::to_string(GameContext::getMapSize()));
    }

    std::string getName() override { return "SettingsPage"; }

private:
    sf::Vector2f windowSize;

    std::unordered_map<std::string, int> vars;

    static void subPlayers(std::vector<void *> parameters)
    {
        GameContext::setNumPlayers(GameContext::getPlayersNumber() - 1);
    }

    static void subMapSize(std::vector<void *> parameters)
    {
        GameContext::setMapSize(GameContext::getMapSize() - 1);
    }

    static void addPlayers(std::vector<void *> parameters)
    {
        GameContext::setNumPlayers(GameContext::getPlayersNumber() + 1);
    }

    static void addMapSize(std::vector<void *> parameters)
    {
        GameContext::setMapSize(GameContext::getMapSize() + 1);
    }
};

#endif // SETTINGSPAGE_HPP
