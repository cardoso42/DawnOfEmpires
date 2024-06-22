#ifndef SETTINGSPAGE_HPP
#define SETTINGSPAGE_HPP

#include "GenericMenu.hpp"
#include "Callbacks.hpp"
#include <WindowManager.hpp>
#include <cassert>

class SettingsPage : public GenericMenu
{
public:
    SettingsPage(sf::Vector2f windowSize) : windowSize(windowSize), GenericMenu(windowSize)
    {
        assert(instance == nullptr);
        instance = this;

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
        addButton(ButtonMenu("", buttons[0][2].getSize(), false)); // empty button to fill the column
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

    ~SettingsPage()
    {
        instance = nullptr;
    }

    void update() override
    {
        buttons[1][0].updateText("Jogadores: " + std::to_string(GameContext::getPlayersNumber()));
        buttons[1][1].updateText("Tamanho do mapa: " + std::to_string(GameContext::getMapSize()));
    }

    std::string getName() override { return "SettingsPage"; }

private:
    sf::Vector2f windowSize;

    static void subPlayers(std::vector<void *> parameters)
    {
        GameContext::setNumPlayers(GameContext::getPlayersNumber() - 1);

        if (GameContext::getPlayersNumber() <= 1)
        {
            instance->buttons[0][0].setSelectable(false);
        }

        if (GameContext::getPlayersNumber() < GameContext::getMaxPlayersNumber())
        {
            instance->buttons[2][0].setSelectable(true);
        }
    }

    static void subMapSize(std::vector<void *> parameters)
    {
        GameContext::setMapSize(GameContext::getMapSize() - 1);

        if (GameContext::getMapSize() <= 1)
        {
            instance->buttons[0][1].setSelectable(false);
        }

        if (GameContext::getMapSize() < GameContext::getMaxMapSize())
        {
            instance->buttons[2][1].setSelectable(true);
        }
    }

    static void addPlayers(std::vector<void *> parameters)
    {
        GameContext::setNumPlayers(GameContext::getPlayersNumber() + 1);

        if (GameContext::getPlayersNumber() >= GameContext::getMaxPlayersNumber())
        {
            instance->buttons[2][0].setSelectable(false);
        }

        if (GameContext::getPlayersNumber() > 0)
        {
            instance->buttons[0][0].setSelectable(true);
        }
    }

    static void addMapSize(std::vector<void *> parameters)
    {
        GameContext::setMapSize(GameContext::getMapSize() + 1);

        if (GameContext::getMapSize() >= GameContext::getMaxMapSize())
        {
            instance->buttons[2][1].setSelectable(false);
        }

        if (GameContext::getMapSize() > 0)
        {
            instance->buttons[0][1].setSelectable(true);
        }
    }

    // instancia da classe
    static SettingsPage* instance;
};

SettingsPage* SettingsPage::instance = nullptr;

#endif // SETTINGSPAGE_HPP
