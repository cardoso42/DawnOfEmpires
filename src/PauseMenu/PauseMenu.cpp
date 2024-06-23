#include "PauseMenu.hpp"
#include "GameContext.hpp"

PauseMenu::PauseMenu(sf::Vector2f windowSize) : GenericMenu(windowSize)
{
    setRandomBackground();

    sf::Vector2f size = {windowSize.x * 0.2f, windowSize.y * 0.05f};
    setButtonSize(size);

    musicVolume = GameContext::getMusicVolume();
    sfxVolume = GameContext::getSfxVolume();

    addButton("(R)esume", resumeBtnCb, {});
    GameContext::addKeyAction(sf::Keyboard::R, resumeBtnCb);
    
    addIncDecControl(new IncrementDecrementControl({windowSize.x * 0.8f, windowSize.y * 0.05f}, "Music volume", &musicVolume, 0, 100));
    addIncDecControl(new IncrementDecrementControl({windowSize.x * 0.8f, windowSize.y * 0.05f}, "SFX volume", &sfxVolume, 0, 100));

    addButton("(F)inish game", goToMainMenuCb, {});
    GameContext::addKeyAction(sf::Keyboard::F, goToMainMenuCb);

    addButton("(E)xit", exitBtnCb, {});
    GameContext::addKeyAction(sf::Keyboard::E, exitBtnCb);

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

void PauseMenu::goToMainMenuCb(std::vector<void *> parameters)
{
    GameContext::notifyEvent(GameContext::GameEvents::MAIN_MENU);
}
