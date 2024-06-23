#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <GameContext.hpp>
#include "GenericMenu.hpp"

namespace Callbacks
{
    void settingsBtnCb(std::vector<void *> parameters)
    {
        if (parameters.size() < 1)
        {
            throw std::logic_error("Missing pointer to Settings Menu");
        }
        else if (parameters.size() < 2)
        {
            throw std::logic_error("Missing pointer to window size");
        }

        MainMenu::addSubMenu(reinterpret_cast<GenericMenu*(*)(sf::Vector2f)>(parameters[0])(*(static_cast<sf::Vector2f*>(parameters[1]))));
    }

    void exitGameBtnCb(std::vector<void *> parameters)
    {
        GameContext::notifyEvent(GameContext::GameEvents::QUIT);
    }

    void startGameBtnCb(std::vector<void *> parameters)
    {
        GameContext::startGame();
    }
}

#endif // CALLBACKS_HPP
