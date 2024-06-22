#include "WinnerScreen.hpp"
#include "GameContext.hpp"

WinnerScreen::WinnerScreen(sf::Vector2f windowSize, Empire winner) : BaseComponent(),
    winnerText("The winner is player " + std::to_string(winner.getId()), AssetManager::GetFont("AmericanCaptain.ttf"), 144),
    goToMenuButton("Go to menu", {windowSize.x * 0.1f, windowSize.y * 0.05f}), overlay(windowSize),
    quitButton("Quit", {windowSize.x * 0.1f, windowSize.y * 0.05f})
{
    int economy = 0, military = 0, culture = 0;
    for (auto tile : winner.getTerritory())
    {
        if (tile->isConstruction() && tile->getTypeName() == "Economy Construction")
        {
            economy++;
        }
        else if (tile->isConstruction() && tile->getTypeName() == "Military Construction")
        {
            military++;
        }
        else if (tile->isConstruction() && tile->getTypeName() == "Culture Construction")
        {
            culture++;
        }
    }

    if (economy > military && economy > culture)
    {
        background = sf::Sprite(*AssetManager::GetTexture("castelo.png"));
    }
    else if (military > economy && military > culture)
    {
        background = sf::Sprite(*AssetManager::GetTexture("napoleon.png"));
    }
    else if (culture > economy && culture > military)
    {
        background = sf::Sprite(*AssetManager::GetTexture("escola-atenas.png"));
    }
    else
    {
        background = sf::Sprite(*AssetManager::GetTexture("empire.png"));
    }

    background.setOrigin(background.getLocalBounds().width * 0.5f, background.getLocalBounds().height * 0.5f);
    background.setScale(windowSize.x / background.getLocalBounds().width, windowSize.y / background.getLocalBounds().height);
    background.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);

    overlay.setFillColor(sf::Color(255, 200, 200, 122));
    overlay.setOrigin(overlay.getLocalBounds().width * 0.5f, overlay.getLocalBounds().height * 0.5f);
    overlay.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);

    goToMenuButton.setCallback([](std::vector<void*>) { GameContext::notifyEvent(GameContext::GameEvents::MAIN_MENU); }, {});
    quitButton.setCallback([](std::vector<void*>) { GameContext::notifyEvent(GameContext::GameEvents::QUIT); }, {});

    winnerText.setFillColor(sf::Color::Black);
    winnerText.setOrigin(winnerText.getLocalBounds().width * 0.5f, winnerText.getLocalBounds().height * 0.5f);
    winnerText.setPosition(windowSize.x * 0.5f, windowSize.y * 0.35f);

    goToMenuButton.setPosition({windowSize.x * 0.3f, windowSize.y * 0.875f});
    quitButton.setPosition({windowSize.x * 0.7f, windowSize.y * 0.875f});
}

void WinnerScreen::update()
{
}

void WinnerScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(overlay);
    target.draw(winnerText);
    target.draw(goToMenuButton);
    target.draw(quitButton);
}

void WinnerScreen::animate(sf::Time deltaTime)
{
}

void WinnerScreen::click(float x, float y)
{
    goToMenuButton.unselect();
    quitButton.unselect();

    if (goToMenuButton.getGlobalBounds().contains({x, y}))
    {
        goToMenuButton.select(x, y);
    }
    else if (quitButton.getGlobalBounds().contains({x, y}))
    {
        quitButton.select(x, y);
    }
}

void WinnerScreen::handleKeyboardInput(sf::Keyboard::Key key)
{
}
