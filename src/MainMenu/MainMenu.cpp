#include "MainMenu.hpp"
#include "GameContext.hpp"
#include "StartingPage.hpp"
#include <cassert>

MainMenu* MainMenu::instance = nullptr;

MainMenu::MainMenu(sf::Vector2f windowSize) : StackMenu(new StartingPage(windowSize)),
    windowSize(windowSize), background("cristo.png")
{
    setRandomBackground();

    assert(instance == nullptr);
    instance = this;
}

MainMenu::~MainMenu()
{
    instance = nullptr;
}

void MainMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    StackMenu::draw(target, states);
}

void MainMenu::startGameBtnCb(std::vector<void *> parameters)
{
    GameContext::startGame();
}

void MainMenu::addSubMenu(GenericMenu *submenu)
{
    if (instance == nullptr)
    {
        return;
    }

    instance->addMenu(submenu);
    instance->setRandomBackground();
}

void MainMenu::goBack()
{
    if (instance == nullptr)
    {
        return;
    }

    instance->goBack();
    instance->setRandomBackground();
}

void MainMenu::setRandomBackground()
{
    auto texture = AssetManager::GetTexture(bgImgs[rand() % bgImgs.size()]);
    background.setTexture(*texture);
    background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
    background.setPosition(windowSize.x / 2, windowSize.y / 2);
    background.fitTo(static_cast<sf::Vector2i>(windowSize), 1);

    getCurrentMenu()->setButtonTransparency(255 * 0.8f);
}
