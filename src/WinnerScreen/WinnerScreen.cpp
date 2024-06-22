#include "WinnerScreen.hpp"
#include "GameContext.hpp"

WinnerScreen::WinnerScreen(sf::Vector2f windowSize, Empire winner) : BaseComponent(),
    winnerText("The winner is player " + std::to_string(winner.getId()), AssetManager::GetFont("AmericanCaptain.ttf"), 50),
    goToMenuButton("Go to menu", {windowSize.x * 0.1f, windowSize.y * 0.05f}),
    quitButton("Quit", {windowSize.x * 0.1f, windowSize.y * 0.05f})
{
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
