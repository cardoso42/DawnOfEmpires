#include "GameController.hpp"

#include <iostream>
#include <sstream>

GameController::GameController(): window("Dawn of Empires", {800, 600})
{
    sf::Vector2u windowSize = window.getWindowSize();

    map = new TileMap(2, {windowSize.x * 0.5f, windowSize.y * 0.5f});

    // setar listener
}

GameController::~GameController()
{

}

void GameController::updateFrame(sf::Time deltaTime)
{
    window.update();

    map->animate(deltaTime);
}

void GameController::render(sf::Color backgroundColor)
{
    window.beginDraw();
    window.draw(*map);
    window.endDraw();
}

void GameController::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        map->click(pos.x, pos.y);
    }
}

sf::RectangleShape GameController::drawDebugSquare(sf::Sprite sprite, sf::Color backgroundColor)
{
    sf::RectangleShape outline({
        sprite.getGlobalBounds().width,
        sprite.getGlobalBounds().height
    });

    outline.setFillColor(backgroundColor);
    outline.setOutlineThickness(2);
    outline.setOutlineColor(sf::Color::Red);
    outline.setPosition(sprite.getPosition());
    outline.setOrigin(outline.getSize() * 0.5f);

    return outline;
}

bool GameController::isOver() { return window.isDone(); }
