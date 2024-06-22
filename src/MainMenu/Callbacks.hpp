#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <GameContext.hpp>
#include "SettingsPage.hpp"

namespace Callbacks
{
    void settingsBtnCb(std::vector<void *> parameters)
    {
        auto size = static_cast<sf::Vector2f>(GameContext::getWindowManager().getSize());
        MainMenu::addSubMenu(new SettingsPage(size));
    }

    void exitGameBtnCb(std::vector<void *> parameters)
    {
        GameContext::notifyEvent(GameContext::GameEvents::QUIT);
    }
}

#endif // CALLBACKS_HPP
