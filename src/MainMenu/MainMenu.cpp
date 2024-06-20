#include "MainMenu.hpp"
#include "GameContext.hpp"

MainMenu::MainMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    const sf::Vector2f buttonSize(windowSize.x * 0.3f, windowSize.y * 0.1f);

    buttons.push_back(ButtonMenu("Start", buttonSize, startGameBtnCb, {}));
    buttons.push_back(ButtonMenu("Load", buttonSize, loadGameBtnCb, {}));
    buttons.push_back(ButtonMenu("Settings", buttonSize, settingsBtnCb, {}));
    buttons.push_back(ButtonMenu("Exit", buttonSize, exitGameBtnCb, {}));

    organizeButtons();
}

void MainMenu::startGameBtnCb(std::vector<void *> parameters)
{
    std::cout << "startGameBtnCb" << std::endl;
    GameContext::startGame();
}

void MainMenu::loadGameBtnCb(std::vector<void *> parameters)
{
    std::cout << "loadGameBtnCb" << std::endl;
}

void MainMenu::settingsBtnCb(std::vector<void *> parameters)
{
    std::cout << "settingsBtnCb" << std::endl;
}

void MainMenu::exitGameBtnCb(std::vector<void *> parameters)
{
    std::cout << "exitGameBtnCb" << std::endl;
}
