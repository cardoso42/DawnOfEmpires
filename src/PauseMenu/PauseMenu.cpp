#include "PauseMenu.hpp"
#include "GameContext.hpp"

PauseMenu::PauseMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    setButtonSize({windowSize.x * 0.8f, windowSize.y * 0.15f});

    addButton("Resume", resumeBtnCb, {});
    addButton("Exit", exitBtnCb, {});

    organizeButtons();
}

void PauseMenu::resumeBtnCb(std::vector<void *> parameters)
{
    GameContext::notifyEvent(GameContext::GameEvents::RESUME);
}

void PauseMenu::exitBtnCb(std::vector<void *> parameters)
{
    GameContext::notifyEvent(GameContext::GameEvents::QUIT);
}
