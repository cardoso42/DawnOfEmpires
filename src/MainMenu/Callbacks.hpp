#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <GameContext.hpp>
#include "SettingsPage.hpp"

namespace Callbacks
{
    void settingsBtnCb(std::vector<void *> parameters)
    {
        auto size = GameContext::getWindowManager().getSize();
        MainMenu::addSubMenu(new SettingsPage({size.x, size.y}));
    }

    void exitGameBtnCb(std::vector<void *> parameters)
    {
        GameContext::notifyEvent(GameContext::GameEvents::QUIT);
    }
}

#endif // CALLBACKS_HPP
