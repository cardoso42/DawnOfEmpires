#include "MainMenu.hpp"
#include "GameContext.hpp"
#include "StartingPage.hpp"
#include <cassert>

MainMenu* MainMenu::instance = nullptr;

MainMenu::MainMenu(sf::Vector2f windowSize) : StackMenu(new StartingPage(windowSize)),
    windowSize(windowSize)
{

    assert(instance == nullptr);
    instance = this;
}

MainMenu::~MainMenu()
{
    instance = nullptr;
}

void MainMenu::addSubMenu(GenericMenu *submenu)
{
    if (instance == nullptr)
    {
        return;
    }

    instance->addMenu(submenu);
}

void MainMenu::goBackMainMenu()
{
    if (instance == nullptr)
    {
        return;
    }

    instance->goBack();
}
