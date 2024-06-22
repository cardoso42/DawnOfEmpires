#include "PauseMenu.hpp"
#include "GameContext.hpp"

PauseMenu::PauseMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    sf::Vector2f size = {windowSize.x * 0.8f, windowSize.y * 0.15f};
    setButtonSize(size);

    musicVolume = GameContext::getMusicVolume();
    sfxVolume = GameContext::getSfxVolume();

    addButton("Resume", resumeBtnCb, {});
    addIncDecControl(new IncrementDecrementControl({windowSize.x * 0.8f, windowSize.y * 0.05f}, "Music volume", &musicVolume, 0, 100));
    addIncDecControl(new IncrementDecrementControl({windowSize.x * 0.8f, windowSize.y * 0.05f}, "SFX volume", &sfxVolume, 0, 100));
    addButton("Exit", exitBtnCb, {});

    organizeMenu();
}

PauseMenu::~PauseMenu()
{
    GameContext::setMusicVolume(musicVolume);
    GameContext::setSfxVolume(sfxVolume);
}

void PauseMenu::resumeBtnCb(std::vector<void *> parameters)
{
    GameContext::notifyEvent(GameContext::GameEvents::RESUME);
}

void PauseMenu::exitBtnCb(std::vector<void *> parameters)
{
    GameContext::notifyEvent(GameContext::GameEvents::QUIT);
}
